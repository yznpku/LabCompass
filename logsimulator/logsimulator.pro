TARGET = logsimulator
TEMPLATE = app
CONFIG += precompile_header c++14
CONFIG -= debug_and_release debug_and_release_target

QT += qml quick quickcontrols2 widgets svg quickwidgets

INCLUDEPATH += \
    src \
    ../common/src \
    ../vendor/QtSuperMacros \
    ../vendor/QHotkey

DEPEND_LIBS += common
DEPEND_VENDOR_LIBS += QtSuperMacros QHotkey
include(../config/dependencies.pri)

mac: LIBS += -framework Carbon
else:win32: LIBS += -luser32
else:unix {
    QT += x11extras
    LIBS += -lX11
}

win32 {
    LIBS += -lPsapi
    dlls.path = $${OUT_PWD}
    dlls.files = win32-dlls/*
    INSTALLS += dlls
}

SOURCES += \
    src/main.cpp \
    src/widget.cpp \
    src/application.cpp

HEADERS += \
    src/widget.h \
    src/application.h

FORMS += \
    resources/widget.ui
