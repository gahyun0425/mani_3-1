// rrt_spline_node.cpp

#include <rclcpp/rclcpp.hpp>
#include <std_msgs/msg/float64_multi_array.hpp>
#include <geometry_msgs/msg/point.hpp>
#include <visualization_msgs/msg/marker_array.hpp>
#include <visualization_msgs/msg/marker.hpp>
#include <random>
#include <vector>
#include <tuple>
#include <limits>
#include <cmath>
#include <algorithm>
#include <Eigen/Dense>

using namespace std::chrono_literals;

// RRT* 노드 구조체
struct TreeNode {
  geometry_msgs::msg::Point point;
  int parent;
  double cost;
};

class RRTSplinePlanner : public rclcpp::Node {
public:
  RRTSplinePlanner()
  : Node("rrt_spline_planner"), gen_(42)
  {
    // 1) 장애물 좌표 구독 (latched)
    rclcpp::QoS qos(1);
    qos.transient_local();
    obstacle_sub_ = create_subscription<std_msgs::msg::Float64MultiArray>(
      "/obstacle_positions", qos,
      std::bind(&RRTSplinePlanner::obstacleCallback, this, std::placeholders::_1)
    );

    // 2) MarkerArray 퍼블리셔
    marker_pub_ = create_publisher<visualization_msgs::msg::MarkerArray>(
      "/rrt_spline/markers", 10
    );

    // 3) 퍼블리시 타이머 (1 Hz)
    timer_ = create_wall_timer(
      1000ms, std::bind(&RRTSplinePlanner::publishMarkers, this)
    );

    // 시작·목표
    start_ = makePoint(0.1435, 0.0, 0.976);
    goal_  = makePoint(0.6,    0.0, 0.57);
  }

private:
  // ── 구독 콜백
  void obstacleCallback(const std_msgs::msg::Float64MultiArray::SharedPtr msg) {
    // 3개씩 (x,y,z)
    const auto &d = msg->data;
    if (d.size() % 3 != 0) {
      RCLCPP_WARN(get_logger(), "Got bad obstacle array size=%zu", d.size());
      return;
    }
    obstacles_.clear();
    for (size_t i = 0; i < d.size(); i += 3) {
      obstacles_.emplace_back(
        makePoint(d[i], d[i+1], d[i+2]),
        0.045, 0.045, 0.0575
      );
    }
    RCLCPP_INFO(get_logger(), "Received %zu obstacles", obstacles_.size());

    // RRT* 실행
    planRRTstar();
  }

  // ── RRT* 플래닝
  void planRRTstar() {
    // 영역, 파라미터
    const double xmin=-0.5, xmax=1.0,
                 ymin=-0.5, ymax=1.0,
                 zmin= 0.0, zmax=1.0;
    const double step=0.05, radius=0.3, goal_bias=0.05;
    const int    max_iter=1000;

    std::uniform_real_distribution<> ux(xmin,xmax),
                                  uy(ymin,ymax),
                                  uz(zmin,zmax),
                                  ub(0,1);

    nodes_.clear();
    nodes_.push_back({ start_, -1, 0.0 });

    for (int it=0; it<max_iter; ++it) {
      // 샘플링
      geometry_msgs::msg::Point rnd =
        (ub(gen_) < goal_bias) ? goal_ 
                               : makePoint(ux(gen_), uy(gen_), uz(gen_));
      int nid = nearestNode(rnd);
      auto new_pt = steer(nodes_[nid].point, rnd, step);
      if (collision(nodes_[nid].point, new_pt)) continue;

      TreeNode new_node{ new_pt, nid,
        nodes_[nid].cost + dist(nodes_[nid].point, new_pt) };

      // 리와이어
      auto nbrs = nearNodes(new_pt, radius);
      for (int j : nbrs) {
        double c = nodes_[j].cost + dist(nodes_[j].point, new_pt);
        if (!collision(nodes_[j].point, new_pt) && c < new_node.cost) {
          new_node.parent = j;
          new_node.cost   = c;
        }
      }

      int id = nodes_.size();
      nodes_.push_back(new_node);
      for (int j : nbrs) {
        double c2 = new_node.cost + dist(new_pt, nodes_[j].point);
        if (!collision(new_pt, nodes_[j].point) && c2 < nodes_[j].cost) {
          nodes_[j].parent = id;
          nodes_[j].cost   = c2;
        }
      }
    }

    // goal 연결 시도
    int gid = nearestNode(goal_);
    if (!collision(nodes_[gid].point, goal_)) {
      TreeNode g{ goal_, gid,
        nodes_[gid].cost + dist(nodes_[gid].point, goal_) };
      nodes_.push_back(g);
      reconstructPath(nodes_.size()-1);
    } else {
      reconstructPath(nearestNode(goal_));
      RCLCPP_INFO(get_logger(), "Goal blocked, used nearest node");
    }

    // spline 준비 (control points)
    splineCP_.clear();
    for (auto &p : best_path_) {
      splineCP_.push_back(Eigen::Vector3d(p.x,p.y,p.z));
    }
    splineDegree_ = 3;
    buildKnots();
  }

  // ── 시각화
  void publishMarkers() {
    visualization_msgs::msg::MarkerArray ma;

    // 1) RRT* 트리 (LINE_LIST, green)
    visualization_msgs::msg::Marker tree;
    tree.header.frame_id = "world";
    tree.header.stamp    = now();
    tree.ns              = "rrt_tree";
    tree.id              = 0;
    tree.type            = visualization_msgs::msg::Marker::LINE_LIST;
    tree.action          = visualization_msgs::msg::Marker::ADD;
    tree.scale.x         = 0.001;
    tree.color.g         = 1.0;
    tree.color.a         = 0.5;
    for (size_t i=1; i<nodes_.size(); ++i) {
      tree.points.push_back(nodes_[i].point);
      tree.points.push_back(nodes_[nodes_[i].parent].point);
    }
    ma.markers.push_back(tree);

    // 2) 최적 경로 (LINE_STRIP, blue)
    visualization_msgs::msg::Marker path;
    path.header.frame_id = "world";
    path.header.stamp    = now();
    path.ns              = "rrt_path";
    path.id              = 1;
    path.type            = visualization_msgs::msg::Marker::LINE_STRIP;
    path.action          = visualization_msgs::msg::Marker::ADD;
    path.scale.x         = 0.005;
    path.color.b         = 1.0;
    path.color.a         = 1.0;
    for (auto &pt : best_path_) {
      path.points.push_back(pt);
    }
    ma.markers.push_back(path);

    // 3) Spline (LINE_STRIP, red)
    if (splineCP_.size() >= splineDegree_ + 1) {
      visualization_msgs::msg::Marker spline;
      spline.header.frame_id = "world";
      spline.header.stamp    = now();
      spline.ns              = "spline_path";
      spline.id              = 2;
      spline.type            = visualization_msgs::msg::Marker::LINE_STRIP;
      spline.action          = visualization_msgs::msg::Marker::ADD;
      spline.scale.x         = 0.005;
      spline.color.r         = 1.0;
      spline.color.a         = 1.0;

      // t 샘플링
      double t0 = knots_[splineDegree_];
      double t1 = knots_[splineCP_.size()];
      for (double t = t0; t <= t1; t += 0.05) {
        Eigen::Vector3d pi = interpolate(t);
        geometry_msgs::msg::Point gp;
        gp.x = pi.x(); gp.y = pi.y(); gp.z = pi.z();
        spline.points.push_back(gp);
      }
      ma.markers.push_back(spline);
    }

    marker_pub_->publish(ma);
  }

  // ── 유틸들
  geometry_msgs::msg::Point makePoint(double x,double y,double z){
    geometry_msgs::msg::Point p; p.x=x; p.y=y; p.z=z; return p;
  }
  double dist(const geometry_msgs::msg::Point &a,
              const geometry_msgs::msg::Point &b){
    return std::hypot(a.x-b.x, a.y-b.y, a.z-b.z);
  }
  int nearestNode(const geometry_msgs::msg::Point &p){
    double best = 1e9; int idx=0;
    for (size_t i=0;i<nodes_.size();++i){
      double d=dist(nodes_[i].point,p);
      if (d<best){ best=d; idx=i; }
    }
    return idx;
  }
  geometry_msgs::msg::Point steer(const geometry_msgs::msg::Point &a,
                                  const geometry_msgs::msg::Point &b,double step){
    double dx=b.x-a.x, dy=b.y-a.y, dz=b.z-a.z;
    double d = std::sqrt(dx*dx+dy*dy+dz*dz);
    if (d<1e-6) return a;
    double t = std::min(step, d);
    return makePoint(a.x+t*dx/d, a.y+t*dy/d, a.z+t*dz/d);
  }
  bool collision(const geometry_msgs::msg::Point &a,
                 const geometry_msgs::msg::Point &b){
    for (auto &obs : obstacles_) {
      auto &[c, rx, ry, rz] = obs;
      double dx=b.x-a.x, dy=b.y-a.y, dz=b.z-a.z;
      double A = dx*dx/(rx*rx)+dy*dy/(ry*ry)+dz*dz/(rz*rz);
      double B = 2*((a.x-c.x)*dx/(rx*rx)
                  +(a.y-c.y)*dy/(ry*ry)
                  +(a.z-c.z)*dz/(rz*rz));
      double C = (a.x-c.x)*(a.x-c.x)/(rx*rx)
               +(a.y-c.y)*(a.y-c.y)/(ry*ry)
               +(a.z-c.z)*(a.z-c.z)/(rz*rz)-1;
      double disc=B*B-4*A*C;
      if (disc<0) continue;
      double t1=(-B+std::sqrt(disc))/(2*A);
      double t2=(-B-std::sqrt(disc))/(2*A);
      if ((t1>=0&&t1<=1)||(t2>=0&&t2<=1)) return true;
    }
    return false;
  }
  void reconstructPath(int idx){
    best_path_.clear();
    for (int i=idx; i>=0; i=nodes_[i].parent)
      best_path_.push_back(nodes_[i].point);
    std::reverse(best_path_.begin(), best_path_.end());
  }

  // ── B-Spline 유틸
  // basis function (De Boor)
  double basis(int i, int k, double t) {
    if (k==0) {
      return (t>=knots_[i] && t<knots_[i+1])?1.0:0.0;
    }
    double d1 = knots_[i+k]   - knots_[i];
    double d2 = knots_[i+k+1] - knots_[i+1];
    double a = (d1==0?0:(t - knots_[i])   / d1 * basis(i,   k-1, t));
    double b = (d2==0?0:(knots_[i+k+1] - t)/ d2 * basis(i+1, k-1, t));
    return a+b;
  }
  // knot 벡터 생성 (open uniform)
  void buildKnots() {
    int n = splineCP_.size();
    int k = splineDegree_;
    knots_.resize(n + k + 1);
    // start repeat
    for (int i=0; i<=k; ++i) knots_[i] = 0;
    // middle uniform
    for (int i=k+1; i<=n-1; ++i) knots_[i] = i - k;
    // end repeat
    for (int i=n; i<=(n+k); ++i) knots_[i] = n - k;
  }
  // t에 대한 위치 보간
  Eigen::Vector3d interpolate(double t) {
    Eigen::Vector3d p(0,0,0);
    int n = splineCP_.size()-1, k=splineDegree_;
    for (int i=0; i<=n; ++i) {
      double B = basis(i, k, t);
      p += B * splineCP_[i];
    }
    return p;
  }

  // 노드 데이터
  rclcpp::Subscription<std_msgs::msg::Float64MultiArray>::SharedPtr obstacle_sub_;
  rclcpp::Publisher<visualization_msgs::msg::MarkerArray>::SharedPtr marker_pub_;
  rclcpp::TimerBase::SharedPtr timer_;

  geometry_msgs::msg::Point start_, goal_;
  std::vector<std::tuple<geometry_msgs::msg::Point,double,double,double>> obstacles_;
  std::vector<TreeNode> nodes_;
  std::vector<geometry_msgs::msg::Point> best_path_;

  // spline
  std::vector<Eigen::Vector3d> splineCP_;
  std::vector<double>          knots_;
  int                          splineDegree_;

  std::mt19937 gen_;
};

int main(int argc, char **argv){
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<RRTSplinePlanner>());
  rclcpp::shutdown();
  return 0;
}
