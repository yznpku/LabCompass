#ifndef HOTKEYBINDING_H
#define HOTKEYBINDING_H

#include "stdafx.h"
#include <QHotkey>

class HotkeyBinding : public QHotkey {
    Q_OBJECT

    QObject* global;
    QObject* settings;
    QString propertyName;

public:
    HotkeyBinding(QObject* global, QObject* settings, QByteArray propertyName, QByteArray propertyChangeSignal);

private slots:
    void rebindHotkey();
    void onOptionsWindowOpenChanged();
};

#endif // HOTKEYBINDING_H
