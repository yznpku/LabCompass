#include "settings.h"

Settings::Settings(const QString& organization, const QString& application, QObject* parent)
  : QSettings(organization, application, parent)
{

}
