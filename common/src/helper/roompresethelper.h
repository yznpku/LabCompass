#ifndef ROOMPRESETHELPER_H
#define ROOMPRESETHELPER_H

#include "stdafx.h"

class RoomPresetHelper
{
  QHash<QString, QList<QPair<QString, QVariantMap>>> cache; // name => [(keyword, preset)]

public:
  static RoomPresetHelper* instance;

public:
  RoomPresetHelper();

  QVariantMap getPreset(const QString& roomName, const QString& areaCode) const;
};

#endif // ROOMPRESETHELPER_H
