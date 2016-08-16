/****************************************************************************
** Meta object code from reading C++ file 'qtcoinviewer.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.6)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "qtcoinviewer.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'qtcoinviewer.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.6. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_QtCoinViewer[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
      20,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      14,   13,   13,   13, 0x0a,
      32,   13,   13,   13, 0x0a,
      52,   13,   13,   13, 0x0a,
      70,   13,   13,   13, 0x0a,
      77,   13,   13,   13, 0x0a,
      96,   13,   13,   13, 0x0a,
     126,   13,   13,   13, 0x0a,
     161,  158,   13,   13, 0x0a,
     181,  158,   13,   13, 0x0a,
     206,  158,   13,   13, 0x0a,
     232,  158,   13,   13, 0x0a,
     257,   13,   13,   13, 0x0a,
     285,  158,   13,   13, 0x0a,
     308,   13,   13,   13, 0x0a,
     342,   13,   13,   13, 0x0a,
     373,  158,   13,   13, 0x0a,
     400,   13,   13,   13, 0x0a,
     417,   13,   13,   13, 0x0a,
     436,   13,   13,   13, 0x0a,
     467,   13,   13,   13, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_QtCoinViewer[] = {
    "QtCoinViewer\0\0LoadEnvironment()\0"
    "ImportEnvironment()\0SaveEnvironment()\0"
    "Quit()\0ViewCameraParams()\0"
    "ViewGeometryChanged(QAction*)\0"
    "ViewDebugLevelChanged(QAction*)\0on\0"
    "ViewToggleFPS(bool)\0ViewToggleFeedBack(bool)\0"
    "RecordRealtimeVideo(bool)\0"
    "RecordSimtimeVideo(bool)\0"
    "VideoCodecChanged(QAction*)\0"
    "ToggleSimulation(bool)\0"
    "CollisionCheckerChanged(QAction*)\0"
    "PhysicsEngineChanged(QAction*)\0"
    "DynamicSelfCollision(bool)\0DynamicGravity()\0"
    "UpdateInterfaces()\0InterfaceSendCommand(QAction*)\0"
    "About()\0"
};

void QtCoinViewer::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        QtCoinViewer *_t = static_cast<QtCoinViewer *>(_o);
        switch (_id) {
        case 0: _t->LoadEnvironment(); break;
        case 1: _t->ImportEnvironment(); break;
        case 2: _t->SaveEnvironment(); break;
        case 3: _t->Quit(); break;
        case 4: _t->ViewCameraParams(); break;
        case 5: _t->ViewGeometryChanged((*reinterpret_cast< QAction*(*)>(_a[1]))); break;
        case 6: _t->ViewDebugLevelChanged((*reinterpret_cast< QAction*(*)>(_a[1]))); break;
        case 7: _t->ViewToggleFPS((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 8: _t->ViewToggleFeedBack((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 9: _t->RecordRealtimeVideo((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 10: _t->RecordSimtimeVideo((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 11: _t->VideoCodecChanged((*reinterpret_cast< QAction*(*)>(_a[1]))); break;
        case 12: _t->ToggleSimulation((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 13: _t->CollisionCheckerChanged((*reinterpret_cast< QAction*(*)>(_a[1]))); break;
        case 14: _t->PhysicsEngineChanged((*reinterpret_cast< QAction*(*)>(_a[1]))); break;
        case 15: _t->DynamicSelfCollision((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 16: _t->DynamicGravity(); break;
        case 17: _t->UpdateInterfaces(); break;
        case 18: _t->InterfaceSendCommand((*reinterpret_cast< QAction*(*)>(_a[1]))); break;
        case 19: _t->About(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData QtCoinViewer::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject QtCoinViewer::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_QtCoinViewer,
      qt_meta_data_QtCoinViewer, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &QtCoinViewer::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *QtCoinViewer::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *QtCoinViewer::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_QtCoinViewer))
        return static_cast<void*>(const_cast< QtCoinViewer*>(this));
    if (!strcmp(_clname, "ViewerBase"))
        return static_cast< ViewerBase*>(const_cast< QtCoinViewer*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int QtCoinViewer::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 20)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 20;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
