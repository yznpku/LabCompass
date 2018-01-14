#ifndef LABYRINTHDATA_H
#define LABYRINTHDATA_H

#include "stdafx.h"

struct LabyrinthData
{
  struct Room
  {
    QString name;
    QString id;
    QPoint coordinate;
    QStringList contents;
    int section;
    bool isFirstRoomInSection {false};
  };
  struct Section
  {
    QStringList roomIds;
    QString firstRoom;
    QString trialRoom;
  };
  using Matrix = QHash<QString, QHash<QString, QList<QString>>>;

  QString difficulty;
  QDate date;

  QString weapon;
  QString sectionMechanics[2];
  QStringList traps;

  QList<Room> rooms;
  Matrix connections;
  Section sections[3];
  QList<std::pair<QString, QString>> goldenDoors;

  QHash<QString, int> roomIdIndex;

public:
  LabyrinthData();
  bool loadFromFile(const QString& fileName);
  bool loadFromString(const QByteArray& str);
  bool loadFromJson(const QJsonObject& json);

  Room getRoomFromId(const QString& id) const;
  bool hasConnection(const QString& from, const QString& to) const;
  bool hasDoorConnection(const QString& from, const QString& to) const;
  bool roomIsFirstRoomInSection(const QString& id) const;
  bool roomIsTrial(const QString& id) const;
  bool roomIsDeadEnd(const QString& id) const;

  qreal roomCost(const QString& id) const;

private:
  bool loadRooms(const QJsonArray& array);
  bool loadConnectionMatrix(const QJsonArray& array);
  bool loadSections();
  bool loadGoldenDoors();
};

#endif // LABYRINTHDATA_H
