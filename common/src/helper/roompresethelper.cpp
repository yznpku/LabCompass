#include "roompresethelper.h"

RoomPresetHelper* RoomPresetHelper::instance = nullptr;

RoomPresetHelper::RoomPresetHelper()
{
  QFile roomPresetsFile(":/room-presets.json");
  roomPresetsFile.open(QIODevice::ReadOnly);
  const auto& roomTypeList = QJsonDocument::fromJson(roomPresetsFile.readAll()).toVariant().toList();

  for (const auto& roomType: roomTypeList) {
    const auto& roomName = roomType.toMap()["roomName"].toString();
    const auto& goldenDoor = roomType.toMap()["goldenDoor"].toBool();
    const auto& variantList = roomType.toMap()["variants"].toList();

    QPair<QString, bool> index {roomName, goldenDoor};
    cacheByNameAndGoldenDoor.insert(index, {});

    for (const auto& variant: variantList) {
      const auto& preset = variant.toMap();
      const auto& areaCode = preset["areaCode"].toString();

      cacheByAreaCode[areaCode] = preset;
      cacheByNameAndGoldenDoor[index].append({areaCode, preset});
    }
  }
}

QVariantMap RoomPresetHelper::getPresetByAreaCode(const QString& areaCode) const
{
  return cacheByAreaCode.value(areaCode, {});
}

QList<QPair<QString, QVariantMap>> RoomPresetHelper::getPresetListByName(const QString& roomName, bool goldenDoor) const
{
  QPair<QString, bool> index {roomName, goldenDoor};
  return cacheByNameAndGoldenDoor[index];
}
