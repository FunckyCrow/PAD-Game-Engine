/****************************************************************************
** Meta object code from reading C++ file 'transformwidget.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.10.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../PAD-Engine/transformwidget.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'transformwidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.10.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_TransformWidget_t {
    QByteArrayData data[12];
    char stringdata0[292];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_TransformWidget_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_TransformWidget_t qt_meta_stringdata_TransformWidget = {
    {
QT_MOC_LITERAL(0, 0, 15), // "TransformWidget"
QT_MOC_LITERAL(1, 16, 7), // "updated"
QT_MOC_LITERAL(2, 24, 0), // ""
QT_MOC_LITERAL(3, 25, 28), // "on_val_Pos_X_editingFinished"
QT_MOC_LITERAL(4, 54, 28), // "on_val_Pos_Y_editingFinished"
QT_MOC_LITERAL(5, 83, 28), // "on_val_Pos_Z_editingFinished"
QT_MOC_LITERAL(6, 112, 28), // "on_val_Rot_X_editingFinished"
QT_MOC_LITERAL(7, 141, 28), // "on_val_Rot_Y_editingFinished"
QT_MOC_LITERAL(8, 170, 28), // "on_val_Rot_Z_editingFinished"
QT_MOC_LITERAL(9, 199, 30), // "on_val_Scale_X_editingFinished"
QT_MOC_LITERAL(10, 230, 30), // "on_val_Scale_Y_editingFinished"
QT_MOC_LITERAL(11, 261, 30) // "on_val_Scale_Z_editingFinished"

    },
    "TransformWidget\0updated\0\0"
    "on_val_Pos_X_editingFinished\0"
    "on_val_Pos_Y_editingFinished\0"
    "on_val_Pos_Z_editingFinished\0"
    "on_val_Rot_X_editingFinished\0"
    "on_val_Rot_Y_editingFinished\0"
    "on_val_Rot_Z_editingFinished\0"
    "on_val_Scale_X_editingFinished\0"
    "on_val_Scale_Y_editingFinished\0"
    "on_val_Scale_Z_editingFinished"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_TransformWidget[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      10,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   64,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       3,    0,   65,    2, 0x08 /* Private */,
       4,    0,   66,    2, 0x08 /* Private */,
       5,    0,   67,    2, 0x08 /* Private */,
       6,    0,   68,    2, 0x08 /* Private */,
       7,    0,   69,    2, 0x08 /* Private */,
       8,    0,   70,    2, 0x08 /* Private */,
       9,    0,   71,    2, 0x08 /* Private */,
      10,    0,   72,    2, 0x08 /* Private */,
      11,    0,   73,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void,

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

       0        // eod
};

void TransformWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        TransformWidget *_t = static_cast<TransformWidget *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->updated(); break;
        case 1: _t->on_val_Pos_X_editingFinished(); break;
        case 2: _t->on_val_Pos_Y_editingFinished(); break;
        case 3: _t->on_val_Pos_Z_editingFinished(); break;
        case 4: _t->on_val_Rot_X_editingFinished(); break;
        case 5: _t->on_val_Rot_Y_editingFinished(); break;
        case 6: _t->on_val_Rot_Z_editingFinished(); break;
        case 7: _t->on_val_Scale_X_editingFinished(); break;
        case 8: _t->on_val_Scale_Y_editingFinished(); break;
        case 9: _t->on_val_Scale_Z_editingFinished(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            typedef void (TransformWidget::*_t)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&TransformWidget::updated)) {
                *result = 0;
                return;
            }
        }
    }
    Q_UNUSED(_a);
}

const QMetaObject TransformWidget::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_TransformWidget.data,
      qt_meta_data_TransformWidget,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *TransformWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *TransformWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_TransformWidget.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int TransformWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 10)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 10;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 10)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 10;
    }
    return _id;
}

// SIGNAL 0
void TransformWidget::updated()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
