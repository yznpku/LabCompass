#ifndef SETTINGS_H
#define SETTINGS_H

#include "stdafx.h"

class Settings : public QObject
{
  Q_OBJECT

  QML_WRITABLE_VAR_PROPERTY(QPoint, mainWindowPosition)
  QML_WRITABLE_VAR_PROPERTY(QString, poeClientPath)
  QML_WRITABLE_VAR_PROPERTY(QString, latestVersion)
  QML_WRITABLE_VAR_PROPERTY(qint64, lastVersionCheckAttempt)
  QML_WRITABLE_VAR_PROPERTY(qint64, lastVersionCheckSuccess)
  QML_WRITABLE_VAR_PROPERTY(bool, portalSkipsSection)
  QML_WRITABLE_VAR_PROPERTY(bool, multiclientSupport)
  QML_WRITABLE_VAR_PROPERTY(QString, importDirectory)
  QML_WRITABLE_VAR_PROPERTY(QString, scaleFactor)

  std::unique_ptr<QSettings> settings;

public:
  Settings(QObject* parent = nullptr);
  void load();
  void save();

//public:
//  Q_INVOKABLE inline void setValue(const QString &key, const QVariant &value) { QSettings::setValue(key, value); }
//  Q_INVOKABLE inline QVariant value(const QString &key, const QVariant &defaultValue = QVariant()) const { return QSettings::value(key, defaultValue); }
};

#endif // SETTINGS_H
