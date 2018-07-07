#include "utils.h"

QJsonValue jsonDocumentToValue(const QJsonDocument& document)
{
  if (document.isArray())
    return document.array();

  if (document.isObject())
    return document.object();

  return QJsonValue();
}
