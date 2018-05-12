TARGET = QHotkey
TEMPLATE = lib
CONFIG += static c++14
CONFIG -= debug_and_release debug_and_release_target

VERSION = 1.2.1

include($$PWD/qhotkey.pri)

DEFINES += QHOTKEY_LIB QHOTKEY_LIB_BUILD

# use INSTALL_ROOT to modify the install location
headers.files = $$PUBLIC_HEADERS
headers.path = $$[QT_INSTALL_HEADERS]
target.path = $$[QT_INSTALL_LIBS]
INSTALLS += target headers

