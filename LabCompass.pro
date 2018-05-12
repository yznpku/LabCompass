TEMPLATE = subdirs
SUBDIRS = \
    app \
    common \
    test \
    logsimulator \
    QtSuperMacros \
    QHotkey

QtSuperMacros.subdir = vendor/QtSuperMacros
QHotkey.subdir = vendor/QHotkey

app.depends = common QHotkey
test.depends = common
common.depends = QtSuperMacros
