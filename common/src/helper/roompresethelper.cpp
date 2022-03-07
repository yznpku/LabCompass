#include "roompresethelper.h"

RoomPresetHelper* RoomPresetHelper::instance = nullptr;

RoomPresetHelper::RoomPresetHelper()
{
    QFile roomPresetsFile(":/room-presets.json");
    roomPresetsFile.open(QIODevice::ReadOnly);
    const auto& roomTypeList = QJsonDocument::fromJson(roomPresetsFile.readAll()).toVariant().toList();

    for (const auto& roomType : roomTypeList) {
        const auto& roomName = roomType.toMap()["roomName"].toString();
        const auto& goldenDoor = roomType.toMap()["goldenDoor"].toBool();
        const auto& variantList = roomType.toMap()["variants"].toList();

        QPair<QString, bool> index { roomName, goldenDoor };
        cacheByNameAndGoldenDoor.insert(index, {});

        for (const auto& variant : variantList) {
            const auto& preset = variant.toMap();
            const auto& areaCode = preset["areaCode"].toString();

            cacheByAreaCode[areaCode] = preset;
            cacheByNameAndGoldenDoor[index].append({ areaCode, preset });
        }
    }
}

Preset RoomPresetHelper::getPresetByAreaCode(const QString& areaCode) const
{
    return cacheByAreaCode.value(areaCode, {});
}

QList<QPair<QString, Preset>> RoomPresetHelper::getPresetListByName(const QString& roomName, bool goldenDoor) const
{
    QPair<QString, bool> index { roomName, goldenDoor };
    return cacheByNameAndGoldenDoor[index];
}

DoorExitLocationModel RoomPresetHelper::getDoorExitLocationModel(const Preset& preset) const
{
    DoorExitLocationModel result;

    for (const auto& direction : preset["doorLocations"].toStringList())
        result.append(QVariantMap { { "direction", direction }, { "tileRect", getTileRect(preset, direction) } });

    return result;
}

ContentLocationModel RoomPresetHelper::getContentLocationModel(const Preset& preset, bool generalLocations, bool majorLocations, bool minorLocations)
{
    ContentLocationModel result;

    const auto& contentLocations = preset["contentLocations"].toMap();

    if (generalLocations && contentLocations.contains("generic")) {
        for (const auto& direction : contentLocations["generic"].toStringList())
            result.append(QVariantMap { { "direction", direction }, { "major", false }, { "tileRect", getTileRect(preset, direction) } });
    }

    if (majorLocations && contentLocations.contains("major")) {
        for (const auto& direction : contentLocations["major"].toStringList())
            result.append(QVariantMap { { "direction", direction }, { "major", true }, { "tileRect", getTileRect(preset, direction) } });
    }

    if (minorLocations && contentLocations.contains("minor")) {
        for (const auto& direction : contentLocations["minor"].toStringList())
            result.append(QVariantMap { { "direction", direction }, { "major", false }, { "tileRect", getTileRect(preset, direction) } });
    }

    return result;
}

QRectF RoomPresetHelper::getTileRect(const Preset& preset, const QString& direction) const
{
    const auto& coord = preset["minimap"].toMap()["directions"].toMap()[direction].toList();
    int row = coord[0].toInt();
    int column = coord[1].toInt();
    int rows = preset["minimap"].toMap()["rows"].toInt();
    int columns = preset["minimap"].toMap()["columns"].toInt();
    qreal rowd = row - (rows - 1) / 2.0;
    qreal columnd = column - (columns - 1) / 2.0;
    qreal scale = 10.0 / std::max(std::max(rows, columns), 7);
    const auto& d = QPointF(columnd - rowd, columnd + rowd) * 0.05 * scale;
    const auto& tileCenter = QPointF(0.5, 0.5) + d;
    return QRectF(tileCenter.x() - 0.05 * scale, tileCenter.y() - 0.05 * scale,
        0.1 * scale, 0.1 * scale);
}
