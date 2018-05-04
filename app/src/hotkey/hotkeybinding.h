#ifndef HOTKEYBINDING_H
#define HOTKEYBINDING_H

#include "stdafx.h"
#include <QHotkey>

class HotkeyBinding : public QHotkey
{
  Q_OBJECT

  QObject* settings;
  QString propertyName;

public:
  HotkeyBinding(QObject* settings, QByteArray propertyName, QByteArray propertyChangeSignal);

private slots:
  void rebindHotkey();
};

#endif // HOTKEYBINDING_H
