#include "hotkeybinding.h"

HotkeyBinding::HotkeyBinding(QObject* global, QObject* settings, QByteArray propertyName, QByteArray propertyChangeSignal)
    : QHotkey()
{
    this->global = global;
    this->settings = settings;
    this->propertyName = propertyName;
    rebindHotkey();

    connect(settings, propertyChangeSignal,
        this, SLOT(rebindHotkey()));
    connect(global, SIGNAL(optionsWindowOpenChanged()),
        this, SLOT(onOptionsWindowOpenChanged()));
}

void HotkeyBinding::rebindHotkey()
{
    setRegistered(false);
    setShortcut(QKeySequence(settings->property(propertyName.toLatin1().constData()).toString()));
    setRegistered(true);
}

void HotkeyBinding::onOptionsWindowOpenChanged()
{
    bool open = global->property("optionsWindowOpen").toBool();
    setRegistered(!open);
}
