#ifndef GLOBAL_H
#define GLOBAL_H

#include "stdafx.h"

static const QString VERSION = "dev-version";

using RoomId = QString;
using DirectionCode = QString; // [""(Unknown), "C"(Secret Passage), "N", "NE", "E", "SE", "S", "SW", "W", "NW"]
using RoomConnections = QHash<RoomId, QList<DirectionCode>>;
using ConnectionMatrix = QHash<RoomId, RoomConnections>;

#endif // GLOBAL_H
