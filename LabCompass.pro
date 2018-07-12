TEMPLATE = subdirs

SUBDIRS = \
    HungarianAlgorithm \
    QtJsonSchema \
    QtSuperMacros \
    QHotkey \
    common \
    test \
    logsimulator \
    app \

CONFIG += ordered

QtSuperMacros.subdir = vendor/QtSuperMacros
QHotkey.subdir = vendor/QHotkey
HungarianAlgorithm.subdir = vendor/HungarianAlgorithm
QtJsonSchema.subdir = vendor/QtJsonSchema
