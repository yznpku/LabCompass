TARGET = common
TEMPLATE = lib
CONFIG += static precompile_header c++14
CONFIG -= debug_and_release debug_and_release_target

QT += qml quick quickcontrols2 widgets svg quickwidgets

PRECOMPILED_HEADER += src/stdafx.h

INCLUDEPATH += \
    src \
    ../vendor/QtSuperMacros

DEPEND_VENDOR_LIBS += QtSuperMacros
include(../config/dependencies.pri)

HEADERS += \
    src/application.h \
    src/model/labyrinthmodel.h \
    src/model/roommodel.h \
    src/model/connectionmodel.h \
    src/model/labyrinthdata.h \
    src/model/navigationdata.h \
    src/model/applicationmodel.h \
    src/window/window.h \
    src/window/headerwindow.h \
    src/window/toolbarwindow.h \
    src/window/compasswindow.h \
    src/window/instructionlistwindow.h \
    src/settings.h \
    src/worker/logwatcher.h \
    src/controller/labyrinthcontroller.h \
    src/window/plannerwindow.h \
    src/model/listmodel.h \
    src/controller/navigationcontroller.h \
    src/model/plandata.h \
    src/model/plannedroutemodel.h \
    src/model/goldendoormodel.h \
    src/model/instructionmodel.h \
    src/window/puzzlewindow.h \
    src/window/optionswindow.h \
    src/model/plansummarymodel.h \
    src/worker/versionchecker.h

SOURCES += \
    src/application.cpp \
    src/model/labyrinthmodel.cpp \
    src/model/roommodel.cpp \
    src/model/connectionmodel.cpp \
    src/model/labyrinthdata.cpp \
    src/model/navigationdata.cpp \
    src/model/applicationmodel.cpp \
    src/window/window.cpp \
    src/window/headerwindow.cpp \
    src/window/toolbarwindow.cpp \
    src/window/compasswindow.cpp \
    src/window/instructionlistwindow.cpp \
    src/settings.cpp \
    src/worker/logwatcher.cpp \
    src/controller/labyrinthcontroller.cpp \
    src/window/plannerwindow.cpp \
    src/model/listmodel.cpp \
    src/controller/navigationcontroller.cpp \
    src/model/plandata.cpp \
    src/model/plannedroutemodel.cpp \
    src/model/goldendoormodel.cpp \
    src/model/instructionmodel.cpp \
    src/window/puzzlewindow.cpp \
    src/window/optionswindow.cpp \
    src/model/plansummarymodel.cpp \
    src/worker/versionchecker.cpp

RESOURCES += \
    resources/labcompass.qrc
