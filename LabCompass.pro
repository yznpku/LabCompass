TEMPLATE = subdirs
SUBDIRS = \
    app \
    common \
    test \
    logsimulator \
    QtSuperMacros \
    QHotkey \
    HungarianAlgorithm

QtSuperMacros.subdir = vendor/QtSuperMacros
QHotkey.subdir = vendor/QHotkey
HungarianAlgorithm.subdir = vendor/HungarianAlgorithm

app.depends = common QHotkey
test.depends = common
common.depends = QtSuperMacros HungarianAlgorithm
