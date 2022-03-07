#include "settings.h"
#include "global.h"

QVariantMap defaultSettings {
    { "mainWindowPosition", QPoint(-1, -1) },
    { "poeClientPath", "" },
    { "latestVersion", "" },
    { "lastVersionCheckAttempt", 0LL },
    { "lastVersionCheckSuccess", 0LL },
    { "lastLoadedMapDate", QDate() },
    { "importDirectory", "" },

    { "multiclientSupport", false },

    { "portalSkipsSection", true },

    { "scaleFactor", "1" },
    { "showMinimap", true },

    { "toggleHideUiHotkey", "" },
};

Settings::Settings(QObject* parent)
    : QObject(parent)
{
    settings.reset(new QSettings("FutureCode", "LabCompass"));

    m_multiclientSupport = false;
    m_portalSkipsSection = true;
    m_showMinimap = true;
}

void Settings::load()
{
    for (auto i = defaultSettings.constBegin(); i != defaultSettings.constEnd(); i++) {
        auto propertyName = i.key();
        auto propertyValue = settings->value(i.key(), i.value());
        setProperty(propertyName.toLocal8Bit().constData(), propertyValue);
    }

    if (settings->value("version").toString() != VERSION) {
        settings->setValue("version", VERSION);
        set_latestVersion("");
        set_lastVersionCheckAttempt(0LL);
        set_lastVersionCheckSuccess(0LL);
    }

    qInfo().noquote() << "Settings loaded" << QJsonDocument::fromVariant(toVariant()).toJson(QJsonDocument::Compact);
}

void Settings::save()
{
    for (auto i = defaultSettings.constBegin(); i != defaultSettings.constEnd(); i++) {
        const auto& propertyName = i.key();
        const auto& propertyValue = property(i.key().toLocal8Bit().constData());
        settings->setValue(propertyName, propertyValue);
    }

    qInfo().noquote() << "Settings saved" << QJsonDocument::fromVariant(toVariant()).toJson(QJsonDocument::Compact);
}

QVariant Settings::toVariant() const
{
    QVariantMap result;
    for (const auto& propertyName : settings->allKeys()) {
        auto value = settings->value(propertyName);

        switch (value.type()) {
        case QVariant::Point:
            value = QVariantMap { { "x", value.toPoint().x() }, { "y", value.toPoint().y() } };
            break;
        case QVariant::Date:
            value = value.toDate().toString("yyyy-MM-dd");
            break;
        default:;
        }

        result[propertyName] = value;
    }
    return result;
}
