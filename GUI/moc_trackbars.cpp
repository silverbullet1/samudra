/****************************************************************************
** Meta object code from reading C++ file 'trackbars.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.2.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "trackbars.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'trackbars.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.2.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_Trackbars_t {
    QByteArrayData data[12];
    char stringdata[296];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    offsetof(qt_meta_stringdata_Trackbars_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData) \
    )
static const qt_meta_stringdata_Trackbars_t qt_meta_stringdata_Trackbars = {
    {
QT_MOC_LITERAL(0, 0, 9),
QT_MOC_LITERAL(1, 10, 34),
QT_MOC_LITERAL(2, 45, 0),
QT_MOC_LITERAL(3, 46, 5),
QT_MOC_LITERAL(4, 52, 34),
QT_MOC_LITERAL(5, 87, 34),
QT_MOC_LITERAL(6, 122, 32),
QT_MOC_LITERAL(7, 155, 34),
QT_MOC_LITERAL(8, 190, 34),
QT_MOC_LITERAL(9, 225, 21),
QT_MOC_LITERAL(10, 247, 23),
QT_MOC_LITERAL(11, 271, 23)
    },
    "Trackbars\0on_horizontalSlider_5_valueChanged\0"
    "\0value\0on_horizontalSlider_4_valueChanged\0"
    "on_horizontalSlider_3_valueChanged\0"
    "on_horizontalSlider_valueChanged\0"
    "on_horizontalSlider_2_valueChanged\0"
    "on_horizontalSlider_6_valueChanged\0"
    "on_pushButton_clicked\0on_pushButton_2_clicked\0"
    "on_pushButton_3_clicked\0"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Trackbars[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       9,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    1,   59,    2, 0x08,
       4,    1,   62,    2, 0x08,
       5,    1,   65,    2, 0x08,
       6,    1,   68,    2, 0x08,
       7,    1,   71,    2, 0x08,
       8,    1,   74,    2, 0x08,
       9,    0,   77,    2, 0x08,
      10,    0,   78,    2, 0x08,
      11,    0,   79,    2, 0x08,

 // slots: parameters
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void Trackbars::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Trackbars *_t = static_cast<Trackbars *>(_o);
        switch (_id) {
        case 0: _t->on_horizontalSlider_5_valueChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: _t->on_horizontalSlider_4_valueChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 2: _t->on_horizontalSlider_3_valueChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 3: _t->on_horizontalSlider_valueChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 4: _t->on_horizontalSlider_2_valueChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 5: _t->on_horizontalSlider_6_valueChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 6: _t->on_pushButton_clicked(); break;
        case 7: _t->on_pushButton_2_clicked(); break;
        case 8: _t->on_pushButton_3_clicked(); break;
        default: ;
        }
    }
}

const QMetaObject Trackbars::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_Trackbars.data,
      qt_meta_data_Trackbars,  qt_static_metacall, 0, 0}
};


const QMetaObject *Trackbars::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Trackbars::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_Trackbars.stringdata))
        return static_cast<void*>(const_cast< Trackbars*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int Trackbars::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 9)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 9;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 9)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 9;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
