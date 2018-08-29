#ifndef GLOBAL_H
#define GLOBAL_H

#include "stdafx.h"

static const QString VERSION = "1.4.1";

using RoomId = QString;
using DirectionCode = QString; // [""(Unknown), "C"(Secret Passage), "N", "NE", "E", "SE", "S", "SW", "W", "NW"]
using RoomConnections = QHash<RoomId, QList<DirectionCode>>;
using ConnectionMatrix = QHash<RoomId, RoomConnections>;

using Preset = QVariantMap;
using DoorExitLocationModel = QVariantList; // ["direction": string, "tileRect": rect]
using ContentLocationModel = QVariantList; // ["direction": string, "major": bool, "tileRect": rect]

#endif // GLOBAL_H
