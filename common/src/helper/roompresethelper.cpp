#include "roompresethelper.h"

RoomPresetHelper* RoomPresetHelper::instance = nullptr;

RoomPresetHelper::RoomPresetHelper()
{
  QFile roomPresetsFile(":/room-presets.json");
  roomPresetsFile.open(QIODevice::ReadOnly);
  const auto& roomTypeList = QJsonDocument::fromJson(roomPresetsFile.readAll()).toVariant().toList();

  for (const auto& roomType: roomTypeList) {
    const auto& roomName = roomType.toMap()["roomName"].toString();
    const auto& variantList = roomType.toMap()["variants"].toList();

    if (!cacheByName.contains(roomName))
      cacheByName.insert(roomName, {});

    for (const auto& variant: variantList) {
      auto keyword = variant.toMap()["keyword"].toString();
      auto preset = variant.toMap();

      cacheByName[roomName].append({keyword, preset});
    }
  }
}

QVariantMap RoomPresetHelper::getPreset(const QString& roomName, const QString& areaCode) const
{
  if (!cacheByName.contains(roomName))
    return {};

  auto variants = cacheByName[roomName];
  foreach (auto variant, variants)
    if (areaCode.contains(variant.first))
      return variant.second;

  return {};
}
