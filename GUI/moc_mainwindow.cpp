/****************************************************************************
** Meta object code from reading C++ file 'mainwindow.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.2.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "mainwindow.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mainwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.2.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_MainWindow_t {
    QByteArrayData data[19];
    char stringdata[177];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    offsetof(qt_meta_stringdata_MainWindow_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData) \
    )
static const qt_meta_stringdata_MainWindow_t qt_meta_stringdata_MainWindow = {
    {
QT_MOC_LITERAL(0, 0, 10),
QT_MOC_LITERAL(1, 11, 7),
QT_MOC_LITERAL(2, 19, 0),
QT_MOC_LITERAL(3, 20, 10),
QT_MOC_LITERAL(4, 31, 8),
QT_MOC_LITERAL(5, 40, 3),
QT_MOC_LITERAL(6, 44, 9),
QT_MOC_LITERAL(7, 54, 7),
QT_MOC_LITERAL(8, 62, 21),
QT_MOC_LITERAL(9, 84, 5),
QT_MOC_LITERAL(10, 90, 21),
QT_MOC_LITERAL(11, 112, 19),
QT_MOC_LITERAL(12, 132, 4),
QT_MOC_LITERAL(13, 137, 1),
QT_MOC_LITERAL(14, 139, 1),
QT_MOC_LITERAL(15, 141, 10),
QT_MOC_LITERAL(16, 152, 10),
QT_MOC_LITERAL(17, 163, 5),
QT_MOC_LITERAL(18, 169, 6)
    },
    "MainWindow\0Enhance\0\0lineDetect\0cv::Mat&\0"
    "img\0Threshold\0process\0on_comboBox_activated\0"
    "index\0on_pushButton_clicked\0"
    "trackFilteredObject\0int&\0x\0y\0cameraFeed\0"
    "drawObject\0frame\0myarea\0"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MainWindow[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       8,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   54,    2, 0x0a,
       3,    1,   55,    2, 0x0a,
       6,    0,   58,    2, 0x0a,
       7,    0,   59,    2, 0x0a,
       8,    1,   60,    2, 0x08,
      10,    0,   63,    2, 0x08,
      11,    3,   64,    2, 0x08,
      16,    4,   71,    2, 0x08,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 4,    5,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    9,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 12, 0x80000000 | 12, 0x80000000 | 4,   13,   14,   15,
    QMetaType::Void, QMetaType::Int, QMetaType::Int, 0x80000000 | 4, QMetaType::Double,   13,   14,   17,   18,

       0        // eod
};

void MainWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        MainWindow *_t = static_cast<MainWindow *>(_o);
        switch (_id) {
        case 0: _t->Enhance(); break;
        case 1: _t->lineDetect((*reinterpret_cast< cv::Mat(*)>(_a[1]))); break;
        case 2: _t->Threshold(); break;
        case 3: _t->process(); break;
        case 4: _t->on_comboBox_activated((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 5: _t->on_pushButton_clicked(); break;
        case 6: _t->trackFilteredObject((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< cv::Mat(*)>(_a[3]))); break;
        case 7: _t->drawObject((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< cv::Mat(*)>(_a[3])),(*reinterpret_cast< double(*)>(_a[4]))); break;
        default: ;
        }
    }
}

const QMetaObject MainWindow::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_MainWindow.data,
      qt_meta_data_MainWindow,  qt_static_metacall, 0, 0}
};


const QMetaObject *MainWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MainWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_MainWindow.stringdata))
        return static_cast<void*>(const_cast< MainWindow*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int MainWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 8)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 8;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 8)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 8;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
