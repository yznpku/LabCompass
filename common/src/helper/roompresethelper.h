#ifndef ROOMPRESETHELPER_H
#define ROOMPRESETHELPER_H

#include "stdafx.h"

class RoomPresetHelper
{
  QHash<QString, QList<QPair<QString, QVariantMap>>> cacheByName; // name => [(keyword, preset)]
  QHash<QPair<QString, bool>, QList<QPair<QString, QVariantMap>>> cacheByNameAndGoldenDoor; // (name, goldenDoor) => [(keyword, preset)]

public:
  static RoomPresetHelper* instance;

public:
  RoomPresetHelper();

  QVariantMap getPreset(const QString& roomName, const QString& areaCode) const;
};

#endif // ROOMPRESETHELPER_H
