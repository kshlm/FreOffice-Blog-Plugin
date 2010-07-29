/****************************************************************************
** Meta object code from reading C++ file 'maiaObject.h'
**
** Created: Thu Jul 29 10:28:21 2010
**      by: The Qt Meta Object Compiler version 62 (Qt 4.6.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "libmaia/maiaObject.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'maiaObject.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.6.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_MaiaObject[] = {

 // content:
       4,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: signature, parameters, type, tag, flags
      19,   12,   11,   11, 0x05,
      57,   55,   11,   11, 0x05,
     101,   93,   11,   11, 0x05,

 // slots: signature, parameters, type, tag, flags
     150,  135,   11,   11, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_MaiaObject[] = {
    "MaiaObject\0\0,reply\0"
    "aresponse(QVariant&,QNetworkReply*)\0"
    ",\0call(QString,const QList<QVariant>)\0"
    ",,reply\0fault(int,QString,QNetworkReply*)\0"
    "response,reply\0parseResponse(QString,QNetworkReply*)\0"
};

const QMetaObject MaiaObject::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_MaiaObject,
      qt_meta_data_MaiaObject, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &MaiaObject::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *MaiaObject::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *MaiaObject::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_MaiaObject))
        return static_cast<void*>(const_cast< MaiaObject*>(this));
    return QObject::qt_metacast(_clname);
}

int MaiaObject::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: aresponse((*reinterpret_cast< QVariant(*)>(_a[1])),(*reinterpret_cast< QNetworkReply*(*)>(_a[2]))); break;
        case 1: call((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< const QList<QVariant>(*)>(_a[2]))); break;
        case 2: fault((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2])),(*reinterpret_cast< QNetworkReply*(*)>(_a[3]))); break;
        case 3: parseResponse((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QNetworkReply*(*)>(_a[2]))); break;
        default: ;
        }
        _id -= 4;
    }
    return _id;
}

// SIGNAL 0
void MaiaObject::aresponse(QVariant & _t1, QNetworkReply * _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void MaiaObject::call(const QString _t1, const QList<QVariant> _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void MaiaObject::fault(int _t1, const QString & _t2, QNetworkReply * _t3)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}
QT_END_MOC_NAMESPACE
