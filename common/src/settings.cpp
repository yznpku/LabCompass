#include "settings.h"
#include "global.h"

QVariantMap defaultSettings {
  {"mainWindowPosition", QPoint(-1, -1)},
  {"poeClientPath", ""},
  {"latestVersion", ""},
  {"lastVersionCheckAttempt", 0LL},
  {"lastVersionCheckSuccess", 0LL},
  {"portalSkipsSection", true},
  {"multiclientSupport", false},
  {"importDirectory", ""},
  {"scaleFactor", "1"},
  {"toggleHideUiHotkey", ""}
};

Settings::Settings(QObject* parent) : QObject(parent)
{
  settings.reset(new QSettings("FutureCode", "LabCompass"));
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

  qInfo() << "Settings loaded";
}

void Settings::save()
{
  for (auto i = defaultSettings.constBegin(); i != defaultSettings.constEnd(); i++) {
    auto propertyName = i.key();
    auto propertyValue = property(i.key().toLocal8Bit().constData());
    settings->setValue(propertyName, propertyValue);
  }

  qInfo() << "Settings saved";
}
