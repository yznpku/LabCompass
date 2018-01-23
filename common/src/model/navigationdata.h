#ifndef NAVIGATIONDATA_H
#define NAVIGATIONDATA_H

#include "stdafx.h"
#include "model/labyrinthdata.h"
#include "model/plandata.h"

struct NavigationData
{
  struct ContentState
  {
    QStringList goldenKeyLocations;
    int goldenKeysInInventory {0};
    QList<std::pair<QString, QString>> lockedDoors;

    int silverKeysInInventory {0};
  };

  const LabyrinthData* lab {nullptr};

  bool currentRoomDetermined;
  QString currentRoom;
  QSet<QString> possibleCurrentRooms;
  QString previousRoom;

  ContentState contentState;

  QStringList targetRooms;
  QStringList plannedRoute;

public:
  void loadFromData(const LabyrinthData* lab, const PlanData& plan);
  void updatePlannedRouteAndInstructions();

private:
  QStringList plannedRouteInsideSection(int section, const QString& begin, const QString& end, const QStringList& targetRooms, ContentState* tempGolden);
  static bool listContainsAll(const QStringList& l1, const QStringList& l2);
};

#endif // NAVIGATIONDATA_H
