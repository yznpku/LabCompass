CONFIG += C++11
unix: QT += x11extras

PUBLIC_HEADERS += $$PWD/qhotkey.h \
        $$PWD/QHotkey

HEADERS += $$PUBLIC_HEADERS \
        $$PWD/qhotkey_p.h

SOURCES += $$PWD/qhotkey.cpp

mac: SOURCES += $$PWD/qhotkey_mac.cpp
else:win32: SOURCES += $$PWD/qhotkey_win.cpp
else:unix: SOURCES += $$PWD/qhotkey_x11.cpp

INCLUDEPATH += $$PWD/QHotkey
