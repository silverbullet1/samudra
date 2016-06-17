/****************************************************************************
** Meta object code from reading C++ file 'trackbars.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.6)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../src/qt_ros/src/trackbars.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'trackbars.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.6. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_Trackbars[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       9,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      17,   11,   10,   10, 0x08,
      57,   11,   10,   10, 0x08,
      97,   11,   10,   10, 0x08,
     137,   11,   10,   10, 0x08,
     175,   11,   10,   10, 0x08,
     215,   11,   10,   10, 0x08,
     255,   10,   10,   10, 0x08,
     279,   10,   10,   10, 0x08,
     305,   10,   10,   10, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_Trackbars[] = {
    "Trackbars\0\0value\0"
    "on_horizontalSlider_5_valueChanged(int)\0"
    "on_horizontalSlider_4_valueChanged(int)\0"
    "on_horizontalSlider_3_valueChanged(int)\0"
    "on_horizontalSlider_valueChanged(int)\0"
    "on_horizontalSlider_2_valueChanged(int)\0"
    "on_horizontalSlider_6_valueChanged(int)\0"
    "on_pushButton_clicked()\0"
    "on_pushButton_2_clicked()\0"
    "on_pushButton_3_clicked()\0"
};

void Trackbars::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
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

const QMetaObjectExtraData Trackbars::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject Trackbars::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_Trackbars,
      qt_meta_data_Trackbars, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &Trackbars::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *Trackbars::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *Trackbars::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_Trackbars))
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
    }
    return _id;
}
QT_END_MOC_NAMESPACE
