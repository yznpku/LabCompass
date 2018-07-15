#include "labyrinthdata.h"
#include <QtJsonSchema>
#include "helper/roompresethelper.h"
#include "helper/directionnormalizer.h"

static const QHash<QString, qreal> ROOM_PREFIX_COST {
  {"Sepulchre", 3},
  {"Estate", 5},
  {"Basilica", 7},
  {"Sanitorium", 8},
  {"Mansion", 9},
  {"Domain", 10},
};

static const QHash<QString, qreal> ROOM_SUFFIX_COST {
  {"Path", 6},
  {"Passage", 6},
  {"Walkways", 8},
  {"Halls", 8},
  {"Annex", 10},
  {"Enclosure", 10},
  {"Crossing", 12},
  {"Atrium", 12},
};

static DirectionNormalizer directionNormalizer;
static JsonSchema mapSchema = JsonSchema::fromVariant(QVariant());

LabyrinthData::LabyrinthData()
{

}

bool LabyrinthData::loadFromFile(const QString& fileName)
{
  QFile file(fileName);
  if (!file.open(QIODevice::ReadOnly))
    return false;
  return loadFromString(file.readAll());
}

bool LabyrinthData::loadFromString(const QByteArray& str)
{
  QJsonDocument doc = QJsonDocument::fromJson(str);
  return doc.isObject() && loadFromJson(doc.object());
}


bool LabyrinthData::loadFromJson(const QJsonObject& json)
{
  if (!mapSchema.isValid()) {
    QFile f(":/map.schema.json");
    f.open(QIODevice::ReadOnly);
    mapSchema = JsonSchema::fromJsonString(f.readAll());
  }

  if (!mapSchema.validate(QJsonValue(json)))
    return false;

  difficulty = json["difficulty"].toString();
  date = QDate::fromString(json["date"].toString(), "yyyy-MM-dd");

  weapon = json["weapon"].toString();
  sectionMechanics[0] = json["phase1"].toString();
  sectionMechanics[1] = json["phase2"].toString();

  if (json["trap1"].toString() != "NoTrap")
    traps.append(json["trap1"].toString());
  if (json["trap2"].toString() != "NoTrap")
    traps.append(json["trap2"].toString());

  if (!(loadRooms(json["rooms"].toArray())))
    return false;

  if (!loadConnectionMatrix(json["rooms"].toArray()))
    return false;

  if (!loadGoldenDoors())
    return false;

  loadContentLocations();

  normalizeDoorDirectionsForAllRooms();

  return true;
}

void LabyrinthData::normalizeDoorDirections(const RoomId& id)
{
  auto helper = RoomPresetHelper::instance;

  const auto& room = getRoomFromId(id);
  const auto& originalConnections = connections[id];
  const auto& preset = helper->getPreset(room.name, room.areaCode);

  if (!preset.isEmpty()) {
    const auto& pattern = preset["doorLocations"].toStringList();
    auto normalized = directionNormalizer.normalize(originalConnections, pattern);
    normalizedConnections[id] = normalized;

    qInfo() << "Normalizing room" << id;
    qInfo() << "Original:" << originalConnections;
    qInfo() << "Pattern:" << pattern;
    qInfo() << "Normalized:" << normalized;

  } else {
    normalizedConnections[id] = originalConnections;
  }
}

void LabyrinthData::normalizeDoorDirectionsForAllRooms()
{
  foreach (const auto& room, rooms)
    normalizeDoorDirections(room.id);
}

LabyrinthData::Room LabyrinthData::getRoomFromId(const RoomId& id) const
{
  return rooms[roomIdIndex.value(id)];
}

bool LabyrinthData::hasConnection(const RoomId& from, const RoomId& to) const
{
  return !connections[from][to].isEmpty();
}

bool LabyrinthData::hasDoorConnection(const RoomId& from, const RoomId& to) const
{
  auto& l = connections[from][to];
  return !l.isEmpty() && l[0] != "C" && l[0] != "P";
}

bool LabyrinthData::roomIsFirstRoomInSection(const RoomId& id) const
{
  const Room& room = getRoomFromId(id);
  return room.isFirstRoomInSection;
}

bool LabyrinthData::roomIsTrial(const RoomId& id) const
{
  const Room& room = rooms[roomIdIndex.value(id)];
  return room.name == "Aspirant's Trial";
}

bool LabyrinthData::roomIsDeadEnd(const RoomId& id) const
{
  if (roomIsFirstRoomInSection(id) || roomIsTrial(id))
    return false;

  int exits = 0;
  for (int i = 0; i < rooms.size(); i++) {
    if (hasDoorConnection(id, rooms[i].id))
      exits += 1;
  }
  return exits == 1;
}

bool LabyrinthData::roomHasSecretPassage(const RoomId& id) const
{
  auto roomConnections = connections[id];
  for (auto i = roomConnections.constBegin(); i != roomConnections.constEnd(); i++)
    if (i.value().contains("C"))
      return true;
  return false;
}

RoomConnections LabyrinthData::getRoomConnections(const RoomId& id) const
{
  return normalizedConnections[id];
}

qreal LabyrinthData::roomCost(const RoomId& id) const
{
  if (roomIsTrial(id))
    return 5;
  auto affixes = getRoomFromId(id).name.split(' ');
  return ROOM_PREFIX_COST[affixes[0]] + ROOM_SUFFIX_COST[affixes[1]];
}

bool LabyrinthData::loadRooms(const QJsonArray& array)
{
  if (array.isEmpty())
    return false;
  rooms.append(Room({"Aspirant\'s Plaza", "labyrinth_airlock", "plaza", {-100, 128}, {}, {}, -1, false}));

  for (int i = 0; i < array.size(); i++) {
    if (!array[i].isObject())
      return false;
    auto roomJson = array[i].toObject();

    Room room;
    room.id = roomJson["id"].toString();
    room.areaCode = roomJson["areacode"].toString();

    // capitalize room name
    QStringList roomNameWords = roomJson["name"].toString().split(' ');
    std::transform(roomNameWords.begin(), roomNameWords.end(), roomNameWords.begin(),
                   [](QString x) { x = x.toLower(); if (x.size()) x[0] = x[0].toUpper(); return x; });
    room.name = roomNameWords.join(' ');

    room.coordinate = QPoint(roomJson["x"].toString().toInt(), roomJson["y"].toString().toInt());

    // convert contents to string list
    auto&& contents = roomJson["contents"].toArray();
    std::transform(contents.begin(), contents.end(), std::back_inserter(room.contents),
                   [](const QJsonValue& x) { return x.toString(); });

    rooms.append(room);
  }

  // create index
  roomIdIndex.clear();
  for (int i = 0; i < rooms.size(); i++)
    roomIdIndex[rooms[i].id] = i;

  return true;
}

bool LabyrinthData::loadConnectionMatrix(const QJsonArray& array)
{
  connections.clear();
  foreach (RoomId i, roomIdIndex.uniqueKeys()) {
    connections[i] = RoomConnections();
    foreach (RoomId j, roomIdIndex.uniqueKeys())
      connections[i][j] = QList<RoomId>();
  }

  for (int i = 0; i < array.size(); i++) {
    if (!array[i].isObject())
      return false;
    auto roomJson = array[i].toObject();
    if (!(roomJson.contains("exits") && roomJson["exits"].isObject()))
      return false;
  }

  for (int i = 0; i < array.size(); i++) {
    auto roomJson = array[i].toObject();
    auto roomId = roomJson["id"].toString();
    auto exitsJson = roomJson["exits"].toObject();
    for (auto i = exitsJson.constBegin(); i != exitsJson.constEnd(); i++) {
      auto toId = i.value().toString();
      auto direction = i.key();
      if (direction != "C")
        connections[roomId][toId].append(direction);
    }
  }

  if (!loadSections())
    return false;

  // add backward connections
  for (int i = 0; i < array.size(); i++) {
    auto roomJson = array[i].toObject();
    auto roomId = roomJson["id"].toString();
    auto exitsJson = roomJson["exits"].toObject();
    for (auto i = exitsJson.constBegin(); i != exitsJson.constEnd(); i++) {
      auto toId = i.value().toString();
      auto direction = i.key();
      if (direction != "C" &&
          !hasConnection(toId, roomId) &&
          !(roomIsTrial(roomId) && rooms[roomIdIndex[toId]].isFirstRoomInSection))
        connections[toId][roomId].append("");
    }
  }

  // add secret passages
  for (int i = 0; i < array.size(); i++) {
    auto roomJson = array[i].toObject();
    auto roomId = roomJson["id"].toString();
    auto exitsJson = roomJson["exits"].toObject();
    for (auto i = exitsJson.constBegin(); i != exitsJson.constEnd(); i++) {
      auto toId = i.value().toString();
      auto direction = i.key();
      if (direction == "C")
        connections[roomId][toId].append("C");
    }
  }

  // add plaza connection
  connections["plaza"][rooms[1].id].append("NW");

  return true;
}

bool LabyrinthData::loadSections()
{
  rooms[1].isFirstRoomInSection = true;
  foreach (const Room& room, rooms)
    if (roomIsTrial(room.id))
      for (auto i = connections[room.id].constBegin(); i != connections[room.id].constEnd(); i++)
        if (!i.value().isEmpty())
          rooms[roomIdIndex.value(i.key())].isFirstRoomInSection = true;

  QList<int> firstRooms;
  QList<int> trialRooms;
  for (int i = 0; i < rooms.size(); i++) {
    if (rooms[i].isFirstRoomInSection)
      firstRooms.append(i);
    if (roomIsTrial(rooms[i].id))
      trialRooms.append(i);
  }

  if (!(firstRooms.size() == 3 && trialRooms.size() == 3))
    return false;

  for (int i = 0; i < 3; i++) {
    sections[i].firstRoom = rooms[firstRooms[i]].id;
    sections[i].trialRoom = rooms[trialRooms[i]].id;
  }

  for (int i = 0; i < 3; i++)
    for (int j = roomIdIndex[sections[i].firstRoom]; j < (i == 2 ? rooms.size() : roomIdIndex[sections[i + 1].firstRoom]); j++) {
      rooms[j].section = i;
      sections[i].roomIds.append(rooms[j].id);
    }

  return true;
}

bool LabyrinthData::loadGoldenDoors()
{
  for (int i = 0; i < rooms.size(); i++)
    if (rooms[i].contents.contains("golden-door"))
      for (int j = i + 1; j < rooms.size(); j++) // golden doors can't lead to rooms before it
        if (!roomIsDeadEnd(rooms[j].id) &&
            hasDoorConnection(rooms[i].id, rooms[j].id) &&
            !rooms[j].contents.contains("golden-key") &&
            rooms[j].coordinate.x() > rooms[i].coordinate.x())
          goldenDoors.append(std::pair<RoomId, RoomId>(rooms[i].id, rooms[j].id));
  return true;
}

void LabyrinthData::loadContentLocations()
{
  auto helper = RoomPresetHelper::instance;

  for (int i = 0; i < rooms.size(); i++) {
    auto& room = rooms[i];
    auto preset = helper->getPreset(room.name, room.areaCode);
    if (preset.isEmpty())
      continue;

    room.contentLocations = preset["contentLocations"].toMap();
  }
}
