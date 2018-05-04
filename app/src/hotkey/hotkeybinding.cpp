#include "hotkeybinding.h"

HotkeyBinding::HotkeyBinding(QObject* settings, QByteArray propertyName, QByteArray propertyChangeSignal) : QHotkey()
{
  this->settings = settings;
  this->propertyName = propertyName;
  rebindHotkey();

  connect(settings, propertyChangeSignal,
          this, SLOT(rebindHotkey()));
}

void HotkeyBinding::rebindHotkey()
{
  setShortcut(QKeySequence(settings->property(propertyName.toLatin1().constData()).toString()));
  setRegistered(true);
}
