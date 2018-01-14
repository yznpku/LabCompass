TEMPLATE = subdirs
SUBDIRS = \
    app \
    common \
    test \
    QtSuperMacros

QtSuperMacros.subdir = vendor/QtSuperMacros

app.depends = common
test.depends = common
common.depends = QtSuperMacros
