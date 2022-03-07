#ifndef ROOMPRESETHELPER_H
#define ROOMPRESETHELPER_H

#include "global.h"
#include "stdafx.h"

class RoomPresetHelper {
    QHash<QString, Preset> cacheByAreaCode; // areaCode => preset
    QHash<QPair<QString, bool>, QList<QPair<QString, Preset>>> cacheByNameAndGoldenDoor; // (name, goldenDoor) => [(areaCode, preset)]

public:
    static RoomPresetHelper* instance;

public:
    RoomPresetHelper();

    Preset getPresetByAreaCode(const QString& areaCode) const;
    QList<QPair<QString, Preset>> getPresetListByName(const QString& roomName, bool goldenDoor) const;

    DoorExitLocationModel getDoorExitLocationModel(const Preset& preset) const;
    ContentLocationModel getContentLocationModel(const Preset& preset, bool generalLocations = true, bool majorLocations = true, bool minorLocations = true);

private:
    QRectF getTileRect(const Preset& preset, const QString& direction) const;
};

#endif // ROOMPRESETHELPER_H
