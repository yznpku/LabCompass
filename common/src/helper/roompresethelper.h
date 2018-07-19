#ifndef ROOMPRESETHELPER_H
#define ROOMPRESETHELPER_H

#include "stdafx.h"

class RoomPresetHelper
{
  QHash<QString, QVariantMap> cacheByAreaCode; // areaCode => preset
  QHash<QPair<QString, bool>, QList<QPair<QString, QVariantMap>>> cacheByNameAndGoldenDoor; // (name, goldenDoor) => [(areaCode, preset)]

public:
  static RoomPresetHelper* instance;

public:
  RoomPresetHelper();

  QVariantMap getPresetByAreaCode(const QString& areaCode) const;
  QList<QPair<QString, QVariantMap>> getPresetListByName(const QString& roomName, bool goldenDoor) const;
};

#endif // ROOMPRESETHELPER_H
