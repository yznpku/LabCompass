#ifndef LABYRINTHDATA_H
#define LABYRINTHDATA_H

#include "stdafx.h"
#include "global.h"

struct LabyrinthData
{
  struct Room
  {
    QString name;
    QString areaCode;
    RoomId id;
    QPoint coordinate;
    QStringList contents;
    QVariantMap contentLocations;
    int section;
    bool isFirstRoomInSection {false};
  };
  struct Section
  {
    QList<RoomId> roomIds;
    RoomId firstRoom;
    RoomId trialRoom;
  };

  QString difficulty;
  QDate date;

  QString weapon;
  QString sectionMechanics[2];
  QStringList traps;

  QList<Room> rooms;
  ConnectionMatrix connections;
  ConnectionMatrix normalizedConnections;
  Section sections[3];
  QList<std::pair<RoomId, RoomId>> goldenDoors;

  QHash<RoomId, int> roomIdIndex;

public:
  LabyrinthData();
  bool loadFromFile(const QString& fileName);
  bool loadFromString(const QByteArray& str);
  bool loadFromJson(const QJsonObject& json);

  void normalizeDoorDirections(const RoomId& id);
  void normalizeDoorDirectionsForAllRooms();

  Room getRoomFromId(const RoomId& id) const;
  bool hasConnection(const RoomId& from, const RoomId& to) const;
  bool hasDoorConnection(const RoomId& from, const RoomId& to) const;
  bool roomIsFirstRoomInSection(const RoomId& id) const;
  bool roomIsTrial(const RoomId& id) const;
  bool roomIsDeadEnd(const RoomId& id) const;
  bool roomHasSecretPassage(const RoomId& id) const;
  RoomConnections getRoomConnections(const RoomId& id) const;

  qreal roomCost(const RoomId& id) const;

private:
  bool loadRooms(const QJsonArray& array);
  bool loadConnectionMatrix(const QJsonArray& array);
  bool loadSections();
  bool loadGoldenDoors();
  void loadContentLocations();
};

#endif // LABYRINTHDATA_H
