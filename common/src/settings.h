#ifndef SETTINGS_H
#define SETTINGS_H

#include "stdafx.h"

class Settings : public QObject {
    Q_OBJECT

    QML_WRITABLE_VAR_PROPERTY(QPoint, mainWindowPosition)
    QML_WRITABLE_VAR_PROPERTY(QString, poeClientPath)
    QML_WRITABLE_VAR_PROPERTY(QString, latestVersion)
    QML_WRITABLE_VAR_PROPERTY(qint64, lastVersionCheckAttempt)
    QML_WRITABLE_VAR_PROPERTY(qint64, lastVersionCheckSuccess)
    QML_WRITABLE_VAR_PROPERTY(QDate, lastLoadedMapDate)
    QML_WRITABLE_VAR_PROPERTY(QString, importDirectory)

    QML_WRITABLE_VAR_PROPERTY(bool, multiclientSupport)

    QML_WRITABLE_VAR_PROPERTY(bool, portalSkipsSection)

    QML_WRITABLE_VAR_PROPERTY(QString, scaleFactor)
    QML_WRITABLE_VAR_PROPERTY(bool, showMinimap)

    QML_WRITABLE_VAR_PROPERTY(QString, toggleHideUiHotkey)

    std::unique_ptr<QSettings> settings;

public:
    Settings(QObject* parent = nullptr);
    void load();
    void save();

private:
    QVariant toVariant() const;
};

#endif // SETTINGS_H
