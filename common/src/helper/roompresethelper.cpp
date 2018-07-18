#include "roompresethelper.h"

RoomPresetHelper* RoomPresetHelper::instance = nullptr;

RoomPresetHelper::RoomPresetHelper()
{
  QFile roomPresetsFile(":/room-presets.json");
  roomPresetsFile.open(QIODevice::ReadOnly);
  auto roomNameList = QJsonDocument::fromJson(roomPresetsFile.readAll()).toVariant().toList();

  for (auto i = roomNameList.constBegin(); i != roomNameList.constEnd(); i++) {
    auto roomName = i->toMap()["roomName"].toString();
    auto variantList = i->toMap()["variants"].toList();
    cache.insert(roomName, {});

    for (auto j = variantList.constBegin(); j != variantList.constEnd(); j++) {
      auto keyword = j->toMap()["keyword"].toString();
      auto preset = j->toMap();

      cache[roomName].append({keyword, preset});
    }
  }
}

QVariantMap RoomPresetHelper::getPreset(const QString& roomName, const QString& areaCode) const
{
  if (!cache.contains(roomName))
    return {};

  auto variants = cache[roomName];
  foreach (auto variant, variants)
    if (areaCode.contains(variant.first))
      return variant.second;

  return {};
}
