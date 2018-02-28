#ifndef SETTINGS_H
#define SETTINGS_H

#include "stdafx.h"

class Settings : public QSettings
{
  Q_OBJECT

public:
  Settings(const QString& organization, const QString& application = QString(), QObject* parent = nullptr);

public:
  Q_INVOKABLE inline void setValue(const QString &key, const QVariant &value) { QSettings::setValue(key, value); }
  Q_INVOKABLE inline QVariant value(const QString &key, const QVariant &defaultValue = QVariant()) const { return QSettings::value(key, defaultValue); }
};

#endif // SETTINGS_H
