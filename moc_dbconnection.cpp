/****************************************************************************
** Meta object code from reading C++ file 'dbconnection.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.3.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "dbconnection.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'dbconnection.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.3.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_DBconnection_t {
    QByteArrayData data[9];
    char stringdata[124];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_DBconnection_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_DBconnection_t qt_meta_stringdata_DBconnection = {
    {
QT_MOC_LITERAL(0, 0, 12),
QT_MOC_LITERAL(1, 13, 15),
QT_MOC_LITERAL(2, 29, 0),
QT_MOC_LITERAL(3, 30, 13),
QT_MOC_LITERAL(4, 44, 2),
QT_MOC_LITERAL(5, 47, 23),
QT_MOC_LITERAL(6, 71, 22),
QT_MOC_LITERAL(7, 94, 24),
QT_MOC_LITERAL(8, 119, 4)
    },
    "DBconnection\0dbCorrectlyOpen\0\0"
    "QSqlDatabase*\0db\0on_submitButton_clicked\0"
    "on_clearButton_clicked\0on_checkBox_stateChanged\0"
    "arg1"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_DBconnection[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   34,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       5,    0,   37,    2, 0x08 /* Private */,
       6,    0,   38,    2, 0x08 /* Private */,
       7,    1,   39,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3,    4,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    8,

       0        // eod
};

void DBconnection::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        DBconnection *_t = static_cast<DBconnection *>(_o);
        switch (_id) {
        case 0: _t->dbCorrectlyOpen((*reinterpret_cast< QSqlDatabase*(*)>(_a[1]))); break;
        case 1: _t->on_submitButton_clicked(); break;
        case 2: _t->on_clearButton_clicked(); break;
        case 3: _t->on_checkBox_stateChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (DBconnection::*_t)(QSqlDatabase * );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&DBconnection::dbCorrectlyOpen)) {
                *result = 0;
            }
        }
    }
}

const QMetaObject DBconnection::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_DBconnection.data,
      qt_meta_data_DBconnection,  qt_static_metacall, 0, 0}
};


const QMetaObject *DBconnection::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *DBconnection::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_DBconnection.stringdata))
        return static_cast<void*>(const_cast< DBconnection*>(this));
    return QWidget::qt_metacast(_clname);
}

int DBconnection::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 4)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 4)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 4;
    }
    return _id;
}

// SIGNAL 0
void DBconnection::dbCorrectlyOpen(QSqlDatabase * _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_END_MOC_NAMESPACE
