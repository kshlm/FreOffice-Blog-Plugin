/****************************************************************************
** Meta object code from reading C++ file 'maiaXmlRpcServer.h'
**
** Created: Thu Jul 29 10:28:23 2010
**      by: The Qt Meta Object Compiler version 62 (Qt 4.6.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "libmaia/maiaXmlRpcServer.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'maiaXmlRpcServer.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.6.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_MaiaXmlRpcServer[] = {

 // content:
       4,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      53,   18,   17,   17, 0x0a,
      95,   17,   17,   17, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_MaiaXmlRpcServer[] = {
    "MaiaXmlRpcServer\0\0method,responseObject,responseSlot\0"
    "getMethod(QString,QObject**,const char**)\0"
    "newConnection()\0"
};

const QMetaObject MaiaXmlRpcServer::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_MaiaXmlRpcServer,
      qt_meta_data_MaiaXmlRpcServer, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &MaiaXmlRpcServer::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *MaiaXmlRpcServer::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *MaiaXmlRpcServer::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_MaiaXmlRpcServer))
        return static_cast<void*>(const_cast< MaiaXmlRpcServer*>(this));
    return QObject::qt_metacast(_clname);
}

int MaiaXmlRpcServer::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: getMethod((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QObject**(*)>(_a[2])),(*reinterpret_cast< const char**(*)>(_a[3]))); break;
        case 1: newConnection(); break;
        default: ;
        }
        _id -= 2;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
