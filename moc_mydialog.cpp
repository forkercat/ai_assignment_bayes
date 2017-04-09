/****************************************************************************
** Meta object code from reading C++ file 'mydialog.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.7)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "mydialog.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mydialog.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.7. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_MyDialog[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       7,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
       9,   33,   33,   33, 0x08,
      34,   33,   33,   33, 0x08,
      57,   33,   33,   33, 0x08,
      83,   33,   33,   33, 0x08,
     114,   33,   33,   33, 0x08,
     139,  164,   33,   33, 0x08,
     168,  164,   33,   33, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_MyDialog[] = {
    "MyDialog\0onImportButtonClicked()\0\0"
    "onClearButtonClicked()\0onTrainingButtonClicked()\0"
    "onTrainingClearButtonClicked()\0"
    "onPredictButtonClicked()\0"
    "criticalMessage(QString)\0msg\0"
    "warningMessage(QString)\0"
};

void MyDialog::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        MyDialog *_t = static_cast<MyDialog *>(_o);
        switch (_id) {
        case 0: _t->onImportButtonClicked(); break;
        case 1: _t->onClearButtonClicked(); break;
        case 2: _t->onTrainingButtonClicked(); break;
        case 3: _t->onTrainingClearButtonClicked(); break;
        case 4: _t->onPredictButtonClicked(); break;
        case 5: _t->criticalMessage((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 6: _t->warningMessage((*reinterpret_cast< QString(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData MyDialog::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject MyDialog::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_MyDialog,
      qt_meta_data_MyDialog, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &MyDialog::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *MyDialog::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *MyDialog::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_MyDialog))
        return static_cast<void*>(const_cast< MyDialog*>(this));
    return QDialog::qt_metacast(_clname);
}

int MyDialog::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 7)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 7;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
