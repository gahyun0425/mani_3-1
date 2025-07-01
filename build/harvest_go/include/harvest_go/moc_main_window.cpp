/****************************************************************************
** Meta object code from reading C++ file 'main_window.hpp'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../../src/harvest_go/include/harvest_go/main_window.hpp"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'main_window.hpp' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_MainWindow_t {
    QByteArrayData data[18];
    char stringdata0[357];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_MainWindow_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_MainWindow_t qt_meta_stringdata_MainWindow = {
    {
QT_MOC_LITERAL(0, 0, 10), // "MainWindow"
QT_MOC_LITERAL(1, 11, 24), // "on_System_All_On_clicked"
QT_MOC_LITERAL(2, 36, 0), // ""
QT_MOC_LITERAL(3, 37, 25), // "on_System_All_Off_clicked"
QT_MOC_LITERAL(4, 63, 24), // "on_Vision_All_On_clicked"
QT_MOC_LITERAL(5, 88, 25), // "on_Vision_All_Off_clicked"
QT_MOC_LITERAL(6, 114, 20), // "on_RealSense_clicked"
QT_MOC_LITERAL(7, 135, 22), // "on_Calibration_clicked"
QT_MOC_LITERAL(8, 158, 15), // "on_YOLO_clicked"
QT_MOC_LITERAL(9, 174, 25), // "on_FoundationPose_clicked"
QT_MOC_LITERAL(10, 200, 14), // "on_TSP_clicked"
QT_MOC_LITERAL(11, 215, 22), // "on_Mani_All_On_clicked"
QT_MOC_LITERAL(12, 238, 23), // "on_Mani_All_Off_clicked"
QT_MOC_LITERAL(13, 262, 16), // "on_Motor_clicked"
QT_MOC_LITERAL(14, 279, 14), // "on_Map_clicked"
QT_MOC_LITERAL(15, 294, 15), // "on_Path_clicked"
QT_MOC_LITERAL(16, 310, 22), // "on_Inverse_Sim_clicked"
QT_MOC_LITERAL(17, 333, 23) // "on_Real_Inverse_clicked"

    },
    "MainWindow\0on_System_All_On_clicked\0"
    "\0on_System_All_Off_clicked\0"
    "on_Vision_All_On_clicked\0"
    "on_Vision_All_Off_clicked\0"
    "on_RealSense_clicked\0on_Calibration_clicked\0"
    "on_YOLO_clicked\0on_FoundationPose_clicked\0"
    "on_TSP_clicked\0on_Mani_All_On_clicked\0"
    "on_Mani_All_Off_clicked\0on_Motor_clicked\0"
    "on_Map_clicked\0on_Path_clicked\0"
    "on_Inverse_Sim_clicked\0on_Real_Inverse_clicked"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MainWindow[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      16,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   94,    2, 0x0a /* Public */,
       3,    0,   95,    2, 0x0a /* Public */,
       4,    0,   96,    2, 0x0a /* Public */,
       5,    0,   97,    2, 0x0a /* Public */,
       6,    0,   98,    2, 0x0a /* Public */,
       7,    0,   99,    2, 0x0a /* Public */,
       8,    0,  100,    2, 0x0a /* Public */,
       9,    0,  101,    2, 0x0a /* Public */,
      10,    0,  102,    2, 0x0a /* Public */,
      11,    0,  103,    2, 0x0a /* Public */,
      12,    0,  104,    2, 0x0a /* Public */,
      13,    0,  105,    2, 0x0a /* Public */,
      14,    0,  106,    2, 0x0a /* Public */,
      15,    0,  107,    2, 0x0a /* Public */,
      16,    0,  108,    2, 0x0a /* Public */,
      17,    0,  109,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void MainWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<MainWindow *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->on_System_All_On_clicked(); break;
        case 1: _t->on_System_All_Off_clicked(); break;
        case 2: _t->on_Vision_All_On_clicked(); break;
        case 3: _t->on_Vision_All_Off_clicked(); break;
        case 4: _t->on_RealSense_clicked(); break;
        case 5: _t->on_Calibration_clicked(); break;
        case 6: _t->on_YOLO_clicked(); break;
        case 7: _t->on_FoundationPose_clicked(); break;
        case 8: _t->on_TSP_clicked(); break;
        case 9: _t->on_Mani_All_On_clicked(); break;
        case 10: _t->on_Mani_All_Off_clicked(); break;
        case 11: _t->on_Motor_clicked(); break;
        case 12: _t->on_Map_clicked(); break;
        case 13: _t->on_Path_clicked(); break;
        case 14: _t->on_Inverse_Sim_clicked(); break;
        case 15: _t->on_Real_Inverse_clicked(); break;
        default: ;
        }
    }
    (void)_a;
}

QT_INIT_METAOBJECT const QMetaObject MainWindow::staticMetaObject = { {
    QMetaObject::SuperData::link<QMainWindow::staticMetaObject>(),
    qt_meta_stringdata_MainWindow.data,
    qt_meta_data_MainWindow,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *MainWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MainWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_MainWindow.stringdata0))
        return static_cast<void*>(this);
    return QMainWindow::qt_metacast(_clname);
}

int MainWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 16)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 16;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 16)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 16;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
