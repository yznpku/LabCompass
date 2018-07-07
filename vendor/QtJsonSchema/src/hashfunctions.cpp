#include "hashfunctions.h"
#include "pointer/jsonpointer.h"

uint qHash(const QJsonValue& json, uint seed)
{
  switch (json.type()) {
  case QJsonValue::Bool:
    return qHash(json.toBool(), seed);
  case QJsonValue::Double:
    return qHash(json.toDouble(), seed);
  case QJsonValue::String:
    return qHash(json.toString(), seed);
  case QJsonValue::Array:
    return qHash(json.toArray(), seed);
  case QJsonValue::Object:
    return qHash(json.toObject(), seed);
  default:
    return qHash(0, seed);
  }
}

uint qHash(const QJsonArray& array, uint seed)
{
  return std::accumulate(array.constBegin(), array.constEnd(), seed, HashCombine());
}

uint qHash(const QJsonObject& object, uint seed)
{
  return std::accumulate(object.constBegin(), object.constEnd(), seed, HashCombine());
}

uint qHash(const JsonPointer& ptr, uint seed)
{
  return qHash(ptr.path, seed);
}
