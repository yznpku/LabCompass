#ifndef NAVIGATIONDATA_H
#define NAVIGATIONDATA_H

#include "model/labyrinthdata.h"
#include "model/plandata.h"
#include "stdafx.h"

struct NavigationData {
    struct ContentState {
        QList<RoomId> goldenKeyLocations;
        int goldenKeysInInventory { 0 };
        QList<std::pair<RoomId, RoomId>> lockedDoors;

        QList<RoomId> portalLocations;
    };

    const LabyrinthData* lab { nullptr };

    bool currentRoomDetermined;
    RoomId currentRoom;
    QSet<RoomId> possibleCurrentRooms;
    RoomId previousRoom;

    ContentState contentState;

    QList<RoomId> targetRooms;
    QList<RoomId> plannedRoute;

public:
    void loadFromData(const LabyrinthData* lab, const PlanData& plan);
    void updatePlannedRouteAndInstructions();

private:
    QList<RoomId> plannedRouteInsideSection(int section, const RoomId& begin, const RoomId& end, const QList<RoomId>& targetRooms, ContentState* tempGolden);
    static bool listContainsAll(const QStringList& l1, const QStringList& l2);
};

#endif // NAVIGATIONDATA_H
