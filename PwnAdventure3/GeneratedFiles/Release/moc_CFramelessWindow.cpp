/****************************************************************************
** Meta object code from reading C++ file 'CFramelessWindow.hpp'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.9.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "stdafx.h"
#include "../../CFramelessWindow.hpp"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'CFramelessWindow.hpp' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.9.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_MouseButtonSignaler_t {
    QByteArrayData data[5];
    char stringdata0[60];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_MouseButtonSignaler_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_MouseButtonSignaler_t qt_meta_stringdata_MouseButtonSignaler = {
    {
QT_MOC_LITERAL(0, 0, 19), // "MouseButtonSignaler"
QT_MOC_LITERAL(1, 20, 16), // "mouseButtonEvent"
QT_MOC_LITERAL(2, 37, 0), // ""
QT_MOC_LITERAL(3, 38, 8), // "QWidget*"
QT_MOC_LITERAL(4, 47, 12) // "QMouseEvent*"

    },
    "MouseButtonSignaler\0mouseButtonEvent\0"
    "\0QWidget*\0QMouseEvent*"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MouseButtonSignaler[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       1,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    2,   19,    2, 0x06 /* Public */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3, 0x80000000 | 4,    2,    2,

       0        // eod
};

void MouseButtonSignaler::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        MouseButtonSignaler *_t = static_cast<MouseButtonSignaler *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->mouseButtonEvent((*reinterpret_cast< QWidget*(*)>(_a[1])),(*reinterpret_cast< QMouseEvent*(*)>(_a[2]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 0:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QWidget* >(); break;
            }
            break;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (MouseButtonSignaler::*_t)(QWidget * , QMouseEvent * );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&MouseButtonSignaler::mouseButtonEvent)) {
                *result = 0;
                return;
            }
        }
    }
}

const QMetaObject MouseButtonSignaler::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_MouseButtonSignaler.data,
      qt_meta_data_MouseButtonSignaler,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *MouseButtonSignaler::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MouseButtonSignaler::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_MouseButtonSignaler.stringdata0))
        return static_cast<void*>(const_cast< MouseButtonSignaler*>(this));
    return QObject::qt_metacast(_clname);
}

int MouseButtonSignaler::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 1)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 1;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 1)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 1;
    }
    return _id;
}

// SIGNAL 0
void MouseButtonSignaler::mouseButtonEvent(QWidget * _t1, QMouseEvent * _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
struct qt_meta_stringdata_CFramelessWindow_t {
    QByteArrayData data[18];
    char stringdata0[323];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_CFramelessWindow_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_CFramelessWindow_t qt_meta_stringdata_CFramelessWindow = {
    {
QT_MOC_LITERAL(0, 0, 16), // "CFramelessWindow"
QT_MOC_LITERAL(1, 17, 21), // "windowIconLeftClicked"
QT_MOC_LITERAL(2, 39, 0), // ""
QT_MOC_LITERAL(3, 40, 22), // "windowIconRightClicked"
QT_MOC_LITERAL(4, 63, 18), // "windowIconDblClick"
QT_MOC_LITERAL(5, 82, 14), // "setWindowTitle"
QT_MOC_LITERAL(6, 97, 4), // "text"
QT_MOC_LITERAL(7, 102, 13), // "setWindowIcon"
QT_MOC_LITERAL(8, 116, 3), // "ico"
QT_MOC_LITERAL(9, 120, 16), // "on_retranslateUi"
QT_MOC_LITERAL(10, 137, 26), // "on_applicationStateChanged"
QT_MOC_LITERAL(11, 164, 20), // "Qt::ApplicationState"
QT_MOC_LITERAL(12, 185, 5), // "state"
QT_MOC_LITERAL(13, 191, 25), // "on_minimizeButton_clicked"
QT_MOC_LITERAL(14, 217, 24), // "on_restoreButton_clicked"
QT_MOC_LITERAL(15, 242, 25), // "on_maximizeButton_clicked"
QT_MOC_LITERAL(16, 268, 22), // "on_closeButton_clicked"
QT_MOC_LITERAL(17, 291, 31) // "on_windowTitlebar_doubleClicked"

    },
    "CFramelessWindow\0windowIconLeftClicked\0"
    "\0windowIconRightClicked\0windowIconDblClick\0"
    "setWindowTitle\0text\0setWindowIcon\0ico\0"
    "on_retranslateUi\0on_applicationStateChanged\0"
    "Qt::ApplicationState\0state\0"
    "on_minimizeButton_clicked\0"
    "on_restoreButton_clicked\0"
    "on_maximizeButton_clicked\0"
    "on_closeButton_clicked\0"
    "on_windowTitlebar_doubleClicked"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_CFramelessWindow[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      12,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   74,    2, 0x06 /* Public */,
       3,    0,   75,    2, 0x06 /* Public */,
       4,    0,   76,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       5,    1,   77,    2, 0x0a /* Public */,
       7,    1,   80,    2, 0x0a /* Public */,
       9,    0,   83,    2, 0x0a /* Public */,
      10,    1,   84,    2, 0x08 /* Private */,
      13,    0,   87,    2, 0x08 /* Private */,
      14,    0,   88,    2, 0x08 /* Private */,
      15,    0,   89,    2, 0x08 /* Private */,
      16,    0,   90,    2, 0x08 /* Private */,
      17,    0,   91,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void, QMetaType::QString,    6,
    QMetaType::Void, QMetaType::QIcon,    8,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 11,   12,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void CFramelessWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        CFramelessWindow *_t = static_cast<CFramelessWindow *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->windowIconLeftClicked(); break;
        case 1: _t->windowIconRightClicked(); break;
        case 2: _t->windowIconDblClick(); break;
        case 3: _t->setWindowTitle((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 4: _t->setWindowIcon((*reinterpret_cast< const QIcon(*)>(_a[1]))); break;
        case 5: _t->on_retranslateUi(); break;
        case 6: _t->on_applicationStateChanged((*reinterpret_cast< Qt::ApplicationState(*)>(_a[1]))); break;
        case 7: _t->on_minimizeButton_clicked(); break;
        case 8: _t->on_restoreButton_clicked(); break;
        case 9: _t->on_maximizeButton_clicked(); break;
        case 10: _t->on_closeButton_clicked(); break;
        case 11: _t->on_windowTitlebar_doubleClicked(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (CFramelessWindow::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&CFramelessWindow::windowIconLeftClicked)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (CFramelessWindow::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&CFramelessWindow::windowIconRightClicked)) {
                *result = 1;
                return;
            }
        }
        {
            typedef void (CFramelessWindow::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&CFramelessWindow::windowIconDblClick)) {
                *result = 2;
                return;
            }
        }
    }
}

const QMetaObject CFramelessWindow::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_CFramelessWindow.data,
      qt_meta_data_CFramelessWindow,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *CFramelessWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *CFramelessWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_CFramelessWindow.stringdata0))
        return static_cast<void*>(const_cast< CFramelessWindow*>(this));
    return QWidget::qt_metacast(_clname);
}

int CFramelessWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 12)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 12;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 12)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 12;
    }
    return _id;
}

// SIGNAL 0
void CFramelessWindow::windowIconLeftClicked()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void CFramelessWindow::windowIconRightClicked()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}

// SIGNAL 2
void CFramelessWindow::windowIconDblClick()
{
    QMetaObject::activate(this, &staticMetaObject, 2, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
