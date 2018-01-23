#include "instructionmodel.h"

static const QStringList LOOT_LIST = {
  "Switch puzzle",
  "Floor puzzle",
  "Escort gauntlet",
  "Trap gauntlet",
  "darkshrine",
  "argus",
  "golden-key",
  "silver-key",
  "silver-door",
};
static const QStringList DIRECTION_LIST = {"N", "NE", "E", "SE", "S", "SW", "W", "NW"};

InstructionModel::InstructionModel(QObject* parent) : QObject(parent)
{
  m_roomHasPortal = false;
  m_atPlaza = false;
  m_atTrialRoom = false;
  m_hasNextRoom = false;
  m_nextRoomIsPreviousRoom = false;
  m_nextRoomIsUnmarkedOppositeDirection = false;
  m_finishedSections = 0;
  m_currentSection = -1;
  m_shouldKillIzaro = false;
}

void InstructionModel::loadFromData(const NavigationData& data)
{
  if (!data.currentRoomDetermined)
    return;

  auto contents = data.lab->getRoomFromId(data.currentRoom).contents;
  QStringList loot;
  std::copy_if(contents.constBegin(), contents.constEnd(), std::back_inserter(loot),
               [](const QString& content) { return LOOT_LIST.contains(content); });
  update_roomLoot(loot);

  auto exits = data.lab->connections[data.currentRoom];
  QStringList doorExitDirections;
  for (auto i = exits.constBegin(); i != exits.constEnd(); i++)
    for (auto j = i.value().constBegin(); j != i.value().constEnd(); j++)
      if (DIRECTION_LIST.contains(*j))
        doorExitDirections.append(*j);
  update_roomDoorExitDirections(doorExitDirections);

  update_currentSection(data.lab->getRoomFromId(data.currentRoom).section);

  update_roomHasPortal(false);

  update_atPlaza(data.currentRoom == "plaza");

  update_atTrialRoom(data.lab->roomIsTrial(data.currentRoom));

  update_hasNextRoom(data.plannedRoute.size() >= 2);

  if (get_hasNextRoom()) {
    auto nextRoomId = data.plannedRoute[1];
    auto connections = data.lab->connections[data.currentRoom][nextRoomId];

    update_nextRoomIsPreviousRoom(nextRoomId == data.previousRoom);

    update_nextRoomIsUnmarkedOppositeDirection(!get_nextRoomIsPreviousRoom() &&
                                               data.lab->roomIsTrial(data.currentRoom) &&
                                               data.lab->getRoomFromId(data.currentRoom).section == data.lab->getRoomFromId(nextRoomId).section);

    update_nextRoomName(data.lab->getRoomFromId(nextRoomId).name);

    if (connections.isEmpty())
      update_nextRoomConnectionType("none"); // should not happen
    else if (connections.contains("P"))
      update_nextRoomConnectionType("portal");
    else if (connections.first() == "C")
      update_nextRoomConnectionType("secret");
    else
      update_nextRoomConnectionType("door");

    update_nextRoomDirection(connections.isEmpty() ? "" : connections.first());
  }

  if (data.lab->roomIsTrial(data.currentRoom)) {
    update_shouldKillIzaro(data.plannedRoute.size() < 2 ||
                           data.lab->getRoomFromId(data.currentRoom).section < data.lab->getRoomFromId(data.plannedRoute[1]).section);

    update_izaroMechanics(get_currentSection() < 2 ? data.lab->sectionMechanics[get_currentSection()] : "");
  }
}
