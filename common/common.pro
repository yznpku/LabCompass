TARGET = common
TEMPLATE = lib
CONFIG += static precompile_header c++14
CONFIG -= debug_and_release debug_and_release_target

QT += qml quick quickcontrols2 widgets svg quickwidgets

PRECOMPILED_HEADER += src/stdafx.h

INCLUDEPATH += \
    src \
    ../vendor/QtSuperMacros \
    ../vendor/HungarianAlgorithm

HEADERS += \
    src/model/labyrinthmodel.h \
    src/model/roommodel.h \
    src/model/connectionmodel.h \
    src/model/labyrinthdata.h \
    src/model/navigationdata.h \
    src/model/applicationmodel.h \
    src/settings.h \
    src/worker/logwatcher.h \
    src/controller/labyrinthcontroller.h \
    src/model/listmodel.h \
    src/controller/navigationcontroller.h \
    src/model/plandata.h \
    src/model/plannedroutemodel.h \
    src/model/goldendoormodel.h \
    src/model/instructionmodel.h \
    src/model/plansummarymodel.h \
    src/worker/versionchecker.h \
    src/global.h \
    src/helper/roompresethelper.h \
    src/worker/datechecker.h \
    src/helper/directionnormalizer.h

SOURCES += \
    src/model/labyrinthmodel.cpp \
    src/model/roommodel.cpp \
    src/model/connectionmodel.cpp \
    src/model/labyrinthdata.cpp \
    src/model/navigationdata.cpp \
    src/model/applicationmodel.cpp \
    src/settings.cpp \
    src/worker/logwatcher.cpp \
    src/controller/labyrinthcontroller.cpp \
    src/model/listmodel.cpp \
    src/controller/navigationcontroller.cpp \
    src/model/plandata.cpp \
    src/model/plannedroutemodel.cpp \
    src/model/goldendoormodel.cpp \
    src/model/instructionmodel.cpp \
    src/model/plansummarymodel.cpp \
    src/worker/versionchecker.cpp \
    src/helper/roompresethelper.cpp \
    src/worker/datechecker.cpp \
    src/helper/directionnormalizer.cpp

RESOURCES += \
    resources/common.qrc
