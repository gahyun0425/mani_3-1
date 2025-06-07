#include <iostream>
#include <Eigen/Dense>
#include <vector>
#include <cmath>

using namespace std;
using namespace Eigen;

// DH 파라미터 구조체 정의
struct DHParam {
    double theta; 
    double a;
    double d;
    double alpha;
};

// DH 파라미터를 이용한 변환 행렬 계산 함수
Matrix4d dhToMatrix(const DHParam& dh) {
    Matrix4d T;
    double ct = cos(dh.theta);
    double st = sin(dh.theta);
    double ca = cos(dh.alpha);
    double sa = sin(dh.alpha);

    T << ct, -st, 0, dh.a,
         st * ca, ct * ca, -sa, -dh.d * sa,
         st * sa, ct * sa, ca, dh.d * ca,
         0, 0, 0, 1;

    return T;
}

// Forward Kinematics 계산 함수
Matrix4d forwardKinematics(const vector<DHParam>& dh_params) {
    Matrix4d T = Matrix4d::Identity();
    for (const auto& dh : dh_params) {
        T *= dhToMatrix(dh);
    }
    return T;
}

int main() {
    // 초기 DH 파라미터 설정 (관절각은 0으로 초기화)
    vector<DHParam> dh_params = {
        {0, 0.0, 0.445, 0}, // theta, a, d, alpha
        {0, 0.0, 0.0, M_PI/2},
        {0, 0.0, 0.27, - M_PI/2},
        {0, 0.0, 0.0, M_PI/2},
        {0, 0.0, 0.24, -M_PI/2},
        {0, 0.0, 0.0, M_PI/2},
        {0, 0.14, 0.05, -M_PI/2}
    };

    // 사용자로부터 각 관절의 관절각 입력 받기
    for (size_t i = 0; i < dh_params.size()-1; ++i) {  // size_t 타입으로 변경
        cout << "Enter joint angle (in degrees) for joint " << i + 1 << ": ";
        double angle_deg;
        cin >> angle_deg;
        dh_params[i].theta = angle_deg * M_PI / 180.0; // degrees to radians
    }

    // Forward Kinematics 계산
    Matrix4d T_06 = forwardKinematics(dh_params);

    // 위치 값 (cm 단위로 변환)
    double x = T_06(0, 3) * 100.0;
    double y = T_06(1, 3) * 100.0;
    double z = T_06(2, 3) * 100.0;

    // 결과 출력
    cout << "Position and Orientation:\n";
    cout << "Position (X, Y, Z) in cm: " << x << " " << y << " " << z << " " << endl;

    return 0;
}