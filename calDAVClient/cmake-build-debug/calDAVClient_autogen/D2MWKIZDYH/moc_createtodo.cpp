/****************************************************************************
** Meta object code from reading C++ file 'createtodo.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../Headers/createtodo.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'createtodo.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_createTodo_t {
    QByteArrayData data[10];
    char stringdata0[116];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_createTodo_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_createTodo_t qt_meta_stringdata_createTodo = {
    {
QT_MOC_LITERAL(0, 0, 10), // "createTodo"
QT_MOC_LITERAL(1, 11, 8), // "createTd"
QT_MOC_LITERAL(2, 20, 0), // ""
QT_MOC_LITERAL(3, 21, 11), // "std::string"
QT_MOC_LITERAL(4, 33, 7), // "summary"
QT_MOC_LITERAL(5, 41, 4), // "Date"
QT_MOC_LITERAL(6, 46, 9), // "createdOn"
QT_MOC_LITERAL(7, 56, 7), // "dueDate"
QT_MOC_LITERAL(8, 64, 23), // "on_createTodo_2_clicked"
QT_MOC_LITERAL(9, 88, 27) // "on_pushButton_clear_clicked"

    },
    "createTodo\0createTd\0\0std::string\0"
    "summary\0Date\0createdOn\0dueDate\0"
    "on_createTodo_2_clicked\0"
    "on_pushButton_clear_clicked"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_createTodo[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    3,   29,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       8,    0,   36,    2, 0x08 /* Private */,
       9,    0,   37,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3, 0x80000000 | 5, 0x80000000 | 5,    4,    6,    7,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void createTodo::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<createTodo *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->createTd((*reinterpret_cast< const std::string(*)>(_a[1])),(*reinterpret_cast< const Date(*)>(_a[2])),(*reinterpret_cast< const Date(*)>(_a[3]))); break;
        case 1: _t->on_createTodo_2_clicked(); break;
        case 2: _t->on_pushButton_clear_clicked(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (createTodo::*)(std::string const & , Date const & , Date const & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&createTodo::createTd)) {
                *result = 0;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject createTodo::staticMetaObject = { {
    QMetaObject::SuperData::link<QDialog::staticMetaObject>(),
    qt_meta_stringdata_createTodo.data,
    qt_meta_data_createTodo,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *createTodo::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *createTodo::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_createTodo.stringdata0))
        return static_cast<void*>(this);
    return QDialog::qt_metacast(_clname);
}

int createTodo::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 3)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 3;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 3)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 3;
    }
    return _id;
}

// SIGNAL 0
void createTodo::createTd(std::string const & _t1, Date const & _t2, Date const & _t3)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t3))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
