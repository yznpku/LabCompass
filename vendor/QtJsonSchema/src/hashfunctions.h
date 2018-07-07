#ifndef HASHFUNCTIONS_H
#define HASHFUNCTIONS_H

#include <QtCore>

class JsonPointer;

struct HashCombine {
  template <class T>
  uint operator()(uint seed, const T& t) const
  { return seed ^ (qHash(t) + 0x9e3779b9 + (seed << 6) + (seed >> 2)) ; }
};

uint qHash(const QJsonValue& json, uint seed = 0);
uint qHash(const QJsonArray& array, uint seed = 0);
uint qHash(const QJsonObject& object, uint seed = 0);
uint qHash(const JsonPointer& ptr, uint seed = 0);

#endif // HASHFUNCTIONS_H
