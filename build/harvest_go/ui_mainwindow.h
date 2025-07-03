/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.15.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QLocale>
#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindowDesign
{
public:
    QAction *action_Quit;
    QWidget *centralwidget;
    QLabel *system_title;
    QPushButton *System_All_On;
    QPushButton *System_All_Off;
    QLabel *vision_title;
    QPushButton *Vision_All_On;
    QPushButton *Vision_All_Off;
    QPushButton *RealSense;
    QPushButton *Calibration;
    QPushButton *YOLO;
    QPushButton *FoundationPose;
    QPushButton *TSP;
    QLabel *mani_title;
    QPushButton *Mani_All_On;
    QPushButton *Mani_All_Off;
    QPushButton *Motor;
    QPushButton *Map;
    QPushButton *Path;
    QPushButton *Inverse_Sim;
    QPushButton *Real_Inverse;
    QPushButton *Gazebo_Launch;
    QPushButton *RViz;
    QPushButton *SAD_Calibration;

    void setupUi(QMainWindow *MainWindowDesign)
    {
        if (MainWindowDesign->objectName().isEmpty())
            MainWindowDesign->setObjectName(QString::fromUtf8("MainWindowDesign"));
        MainWindowDesign->resize(720, 802);
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/images/icon.png"), QSize(), QIcon::Normal, QIcon::Off);
        MainWindowDesign->setWindowIcon(icon);
        MainWindowDesign->setLocale(QLocale(QLocale::English, QLocale::Australia));
        action_Quit = new QAction(MainWindowDesign);
        action_Quit->setObjectName(QString::fromUtf8("action_Quit"));
        action_Quit->setShortcutContext(Qt::ApplicationShortcut);
        centralwidget = new QWidget(MainWindowDesign);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        system_title = new QLabel(centralwidget);
        system_title->setObjectName(QString::fromUtf8("system_title"));
        system_title->setGeometry(QRect(20, 20, 680, 60));
        QFont font;
        font.setPointSize(22);
        font.setBold(true);
        font.setWeight(75);
        system_title->setFont(font);
        system_title->setStyleSheet(QString::fromUtf8("QLabel {\n"
"                        background-color: #495057;\n"
"                        color: white;\n"
"                        border-radius: 15px;\n"
"                        padding: 15px;\n"
"                        }"));
        system_title->setAlignment(Qt::AlignCenter);
        System_All_On = new QPushButton(centralwidget);
        System_All_On->setObjectName(QString::fromUtf8("System_All_On"));
        System_All_On->setGeometry(QRect(70, 100, 270, 65));
        System_All_On->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"                        font: bold 16pt \"Ubuntu\";\n"
"                        background-color: #28a745;\n"
"                        color: white;\n"
"                        border-radius: 15px;\n"
"                        border: none;\n"
"                        padding: 10px;\n"
"                        }\n"
"                        QPushButton:hover {\n"
"                        background-color: #34ce57;\n"
"                        }\n"
"                        QPushButton:pressed {\n"
"                        background-color: #1e7e34;\n"
"                        }"));
        System_All_Off = new QPushButton(centralwidget);
        System_All_Off->setObjectName(QString::fromUtf8("System_All_Off"));
        System_All_Off->setGeometry(QRect(380, 100, 270, 65));
        System_All_Off->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"                        font: bold 16pt \"Ubuntu\";\n"
"                        background-color: #dc3545;\n"
"                        color: white;\n"
"                        border-radius: 15px;\n"
"                        border: none;\n"
"                        padding: 10px;\n"
"                        }\n"
"                        QPushButton:hover {\n"
"                        background-color: #e85563;\n"
"                        }\n"
"                        QPushButton:pressed {\n"
"                        background-color: #bd2130;\n"
"                        }"));
        vision_title = new QLabel(centralwidget);
        vision_title->setObjectName(QString::fromUtf8("vision_title"));
        vision_title->setGeometry(QRect(20, 190, 330, 50));
        QFont font1;
        font1.setPointSize(18);
        font1.setBold(true);
        font1.setWeight(75);
        vision_title->setFont(font1);
        vision_title->setStyleSheet(QString::fromUtf8("QLabel {\n"
"                        background-color: #007bff;\n"
"                        color: white;\n"
"                        border-radius: 12px;\n"
"                        padding: 12px;\n"
"                        }"));
        vision_title->setAlignment(Qt::AlignCenter);
        Vision_All_On = new QPushButton(centralwidget);
        Vision_All_On->setObjectName(QString::fromUtf8("Vision_All_On"));
        Vision_All_On->setGeometry(QRect(20, 250, 160, 55));
        Vision_All_On->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"                        font: bold 12pt \"Ubuntu\";\n"
"                        background-color: #28a745;\n"
"                        color: white;\n"
"                        border-radius: 12px;\n"
"                        border: none;\n"
"                        padding: 8px;\n"
"                        }\n"
"                        QPushButton:hover {\n"
"                        background-color: #34ce57;\n"
"                        }"));
        Vision_All_Off = new QPushButton(centralwidget);
        Vision_All_Off->setObjectName(QString::fromUtf8("Vision_All_Off"));
        Vision_All_Off->setGeometry(QRect(190, 250, 160, 55));
        Vision_All_Off->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"                        font: bold 12pt \"Ubuntu\";\n"
"                        background-color: #dc3545;\n"
"                        color: white;\n"
"                        border-radius: 12px;\n"
"                        border: none;\n"
"                        padding: 8px;\n"
"                        }\n"
"                        QPushButton:hover {\n"
"                        background-color: #e85563;\n"
"                        }"));
        RealSense = new QPushButton(centralwidget);
        RealSense->setObjectName(QString::fromUtf8("RealSense"));
        RealSense->setGeometry(QRect(20, 320, 330, 50));
        RealSense->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"                        font: 12pt \"Ubuntu\";\n"
"                        background-color: #6c757d;\n"
"                        color: white;\n"
"                        border-radius: 10px;\n"
"                        border: none;\n"
"                        padding: 8px;\n"
"                        text-align: left;\n"
"                        padding-left: 15px;\n"
"                        }\n"
"                        QPushButton:hover {\n"
"                        background-color: #7c858d;\n"
"                        }"));
        Calibration = new QPushButton(centralwidget);
        Calibration->setObjectName(QString::fromUtf8("Calibration"));
        Calibration->setGeometry(QRect(20, 380, 330, 50));
        Calibration->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"                        font: 12pt \"Ubuntu\";\n"
"                        background-color: #6c757d;\n"
"                        color: white;\n"
"                        border-radius: 10px;\n"
"                        border: none;\n"
"                        padding: 8px;\n"
"                        text-align: left;\n"
"                        padding-left: 15px;\n"
"                        }\n"
"                        QPushButton:hover {\n"
"                        background-color: #7c858d;\n"
"                        }"));
        YOLO = new QPushButton(centralwidget);
        YOLO->setObjectName(QString::fromUtf8("YOLO"));
        YOLO->setGeometry(QRect(20, 440, 330, 50));
        YOLO->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"                        font: 12pt \"Ubuntu\";\n"
"                        background-color: #6c757d;\n"
"                        color: white;\n"
"                        border-radius: 10px;\n"
"                        border: none;\n"
"                        padding: 8px;\n"
"                        text-align: left;\n"
"                        padding-left: 15px;\n"
"                        }\n"
"                        QPushButton:hover {\n"
"                        background-color: #7c858d;\n"
"                        }"));
        FoundationPose = new QPushButton(centralwidget);
        FoundationPose->setObjectName(QString::fromUtf8("FoundationPose"));
        FoundationPose->setGeometry(QRect(20, 500, 330, 50));
        FoundationPose->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"                        font: 12pt \"Ubuntu\";\n"
"                        background-color: #6c757d;\n"
"                        color: white;\n"
"                        border-radius: 10px;\n"
"                        border: none;\n"
"                        padding: 8px;\n"
"                        text-align: left;\n"
"                        padding-left: 15px;\n"
"                        }\n"
"                        QPushButton:hover {\n"
"                        background-color: #7c858d;\n"
"                        }"));
        TSP = new QPushButton(centralwidget);
        TSP->setObjectName(QString::fromUtf8("TSP"));
        TSP->setGeometry(QRect(20, 560, 330, 50));
        TSP->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"                        font: 12pt \"Ubuntu\";\n"
"                        background-color: #6c757d;\n"
"                        color: white;\n"
"                        border-radius: 10px;\n"
"                        border: none;\n"
"                        padding: 8px;\n"
"                        text-align: left;\n"
"                        padding-left: 15px;\n"
"                        }\n"
"                        QPushButton:hover {\n"
"                        background-color: #7c858d;\n"
"                        }"));
        mani_title = new QLabel(centralwidget);
        mani_title->setObjectName(QString::fromUtf8("mani_title"));
        mani_title->setGeometry(QRect(370, 190, 330, 50));
        mani_title->setFont(font1);
        mani_title->setStyleSheet(QString::fromUtf8("QLabel {\n"
"                        background-color: #6f42c1;\n"
"                        color: white;\n"
"                        border-radius: 12px;\n"
"                        padding: 12px;\n"
"                        }"));
        mani_title->setAlignment(Qt::AlignCenter);
        Mani_All_On = new QPushButton(centralwidget);
        Mani_All_On->setObjectName(QString::fromUtf8("Mani_All_On"));
        Mani_All_On->setGeometry(QRect(370, 250, 160, 55));
        Mani_All_On->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"                        font: bold 12pt \"Ubuntu\";\n"
"                        background-color: #28a745;\n"
"                        color: white;\n"
"                        border-radius: 12px;\n"
"                        border: none;\n"
"                        padding: 8px;\n"
"                        }\n"
"                        QPushButton:hover {\n"
"                        background-color: #34ce57;\n"
"                        }"));
        Mani_All_Off = new QPushButton(centralwidget);
        Mani_All_Off->setObjectName(QString::fromUtf8("Mani_All_Off"));
        Mani_All_Off->setGeometry(QRect(540, 250, 160, 55));
        Mani_All_Off->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"                        font: bold 12pt \"Ubuntu\";\n"
"                        background-color: #dc3545;\n"
"                        color: white;\n"
"                        border-radius: 12px;\n"
"                        border: none;\n"
"                        padding: 8px;\n"
"                        }\n"
"                        QPushButton:hover {\n"
"                        background-color: #e85563;\n"
"                        }"));
        Motor = new QPushButton(centralwidget);
        Motor->setObjectName(QString::fromUtf8("Motor"));
        Motor->setGeometry(QRect(370, 320, 330, 50));
        Motor->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"                        font: 12pt \"Ubuntu\";\n"
"                        background-color: #6c757d;\n"
"                        color: white;\n"
"                        border-radius: 10px;\n"
"                        border: none;\n"
"                        padding: 8px;\n"
"                        text-align: left;\n"
"                        padding-left: 15px;\n"
"                        }\n"
"                        QPushButton:hover {\n"
"                        background-color: #7c858d;\n"
"                        }"));
        Map = new QPushButton(centralwidget);
        Map->setObjectName(QString::fromUtf8("Map"));
        Map->setGeometry(QRect(370, 380, 330, 50));
        Map->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"                        font: 12pt \"Ubuntu\";\n"
"                        background-color: #6c757d;\n"
"                        color: white;\n"
"                        border-radius: 10px;\n"
"                        border: none;\n"
"                        padding: 8px;\n"
"                        text-align: left;\n"
"                        padding-left: 15px;\n"
"                        }\n"
"                        QPushButton:hover {\n"
"                        background-color: #7c858d;\n"
"                        }"));
        Path = new QPushButton(centralwidget);
        Path->setObjectName(QString::fromUtf8("Path"));
        Path->setGeometry(QRect(370, 440, 330, 50));
        Path->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"                        font: 12pt \"Ubuntu\";\n"
"                        background-color: #6c757d;\n"
"                        color: white;\n"
"                        border-radius: 10px;\n"
"                        border: none;\n"
"                        padding: 8px;\n"
"                        text-align: left;\n"
"                        padding-left: 15px;\n"
"                        }\n"
"                        QPushButton:hover {\n"
"                        background-color: #7c858d;\n"
"                        }"));
        Inverse_Sim = new QPushButton(centralwidget);
        Inverse_Sim->setObjectName(QString::fromUtf8("Inverse_Sim"));
        Inverse_Sim->setGeometry(QRect(370, 500, 330, 50));
        Inverse_Sim->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"                        font: 12pt \"Ubuntu\";\n"
"                        background-color: #6c757d;\n"
"                        color: white;\n"
"                        border-radius: 10px;\n"
"                        border: none;\n"
"                        padding: 8px;\n"
"                        text-align: left;\n"
"                        padding-left: 15px;\n"
"                        }\n"
"                        QPushButton:hover {\n"
"                        background-color: #7c858d;\n"
"                        }"));
        Real_Inverse = new QPushButton(centralwidget);
        Real_Inverse->setObjectName(QString::fromUtf8("Real_Inverse"));
        Real_Inverse->setGeometry(QRect(370, 560, 330, 50));
        Real_Inverse->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"                        font: 12pt \"Ubuntu\";\n"
"                        background-color: #6c757d;\n"
"                        color: white;\n"
"                        border-radius: 10px;\n"
"                        border: none;\n"
"                        padding: 8px;\n"
"                        text-align: left;\n"
"                        padding-left: 15px;\n"
"                        }\n"
"                        QPushButton:hover {\n"
"                        background-color: #7c858d;\n"
"                        }"));
        Gazebo_Launch = new QPushButton(centralwidget);
        Gazebo_Launch->setObjectName(QString::fromUtf8("Gazebo_Launch"));
        Gazebo_Launch->setGeometry(QRect(370, 680, 330, 50));
        Gazebo_Launch->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"                        font: 12pt \"Ubuntu\";\n"
"                        background-color: #17a2b8;\n"
"                        color: white;\n"
"                        border-radius: 10px;\n"
"                        border: none;\n"
"                        padding: 8px;\n"
"                        text-align: left;\n"
"                        padding-left: 15px;\n"
"                        }\n"
"                        QPushButton:hover {\n"
"                        background-color: #20c0db;\n"
"                        }"));
        RViz = new QPushButton(centralwidget);
        RViz->setObjectName(QString::fromUtf8("RViz"));
        RViz->setGeometry(QRect(370, 740, 330, 50));
        RViz->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"                        font: 12pt \"Ubuntu\";\n"
"                        background-color: #17a2b8;\n"
"                        color: white;\n"
"                        border-radius: 10px;\n"
"                        border: none;\n"
"                        padding: 8px;\n"
"                        text-align: left;\n"
"                        padding-left: 15px;\n"
"                        }\n"
"                        QPushButton:hover {\n"
"                        background-color: #20c0db;\n"
"                        }"));
        SAD_Calibration = new QPushButton(centralwidget);
        SAD_Calibration->setObjectName(QString::fromUtf8("SAD_Calibration"));
        SAD_Calibration->setGeometry(QRect(370, 620, 330, 50));
        SAD_Calibration->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"                        font: 12pt \"Ubuntu\";\n"
"                        background-color: #6c757d;\n"
"                        color: white;\n"
"                        border-radius: 10px;\n"
"                        border: none;\n"
"                        padding: 8px;\n"
"                        text-align: left;\n"
"                        padding-left: 15px;\n"
"                        }\n"
"                        QPushButton:hover {\n"
"                        background-color: #7c858d;\n"
"                        }"));
        MainWindowDesign->setCentralWidget(centralwidget);

        retranslateUi(MainWindowDesign);
        QObject::connect(action_Quit, SIGNAL(triggered()), MainWindowDesign, SLOT(close()));

        QMetaObject::connectSlotsByName(MainWindowDesign);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindowDesign)
    {
        MainWindowDesign->setWindowTitle(QCoreApplication::translate("MainWindowDesign", "Vision & Manipulator Control System", nullptr));
        action_Quit->setText(QCoreApplication::translate("MainWindowDesign", "&Quit", nullptr));
#if QT_CONFIG(shortcut)
        action_Quit->setShortcut(QCoreApplication::translate("MainWindowDesign", "Ctrl+Q", nullptr));
#endif // QT_CONFIG(shortcut)
        system_title->setText(QCoreApplication::translate("MainWindowDesign", "INTEGRATED CONTROL SYSTEM", nullptr));
        System_All_On->setText(QCoreApplication::translate("MainWindowDesign", "START ALL SYSTEMS", nullptr));
        System_All_Off->setText(QCoreApplication::translate("MainWindowDesign", "STOP ALL SYSTEMS", nullptr));
        vision_title->setText(QCoreApplication::translate("MainWindowDesign", "VISION SYSTEM", nullptr));
        Vision_All_On->setText(QCoreApplication::translate("MainWindowDesign", "Start All", nullptr));
        Vision_All_Off->setText(QCoreApplication::translate("MainWindowDesign", "Stop All", nullptr));
        RealSense->setText(QCoreApplication::translate("MainWindowDesign", "RealSense Camera", nullptr));
        Calibration->setText(QCoreApplication::translate("MainWindowDesign", "Calibration Node", nullptr));
        YOLO->setText(QCoreApplication::translate("MainWindowDesign", "YOLO Detection", nullptr));
        FoundationPose->setText(QCoreApplication::translate("MainWindowDesign", "FoundationPose", nullptr));
        TSP->setText(QCoreApplication::translate("MainWindowDesign", "TSP Planning", nullptr));
        mani_title->setText(QCoreApplication::translate("MainWindowDesign", "MANIPULATOR SYSTEM", nullptr));
        Mani_All_On->setText(QCoreApplication::translate("MainWindowDesign", "Start All", nullptr));
        Mani_All_Off->setText(QCoreApplication::translate("MainWindowDesign", "Stop All", nullptr));
        Motor->setText(QCoreApplication::translate("MainWindowDesign", "Motor Node", nullptr));
        Map->setText(QCoreApplication::translate("MainWindowDesign", "Map Node (Simulation)", nullptr));
        Path->setText(QCoreApplication::translate("MainWindowDesign", "Path Node", nullptr));
        Inverse_Sim->setText(QCoreApplication::translate("MainWindowDesign", "Inverse Node (Simulation)", nullptr));
        Real_Inverse->setText(QCoreApplication::translate("MainWindowDesign", "Real Inverse Node", nullptr));
        Gazebo_Launch->setText(QCoreApplication::translate("MainWindowDesign", "Gazebo Simulation", nullptr));
        RViz->setText(QCoreApplication::translate("MainWindowDesign", "RViz2 Visualization", nullptr));
        SAD_Calibration->setText(QCoreApplication::translate("MainWindowDesign", "SAD Calibration", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindowDesign: public Ui_MainWindowDesign {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
