#include "plansummarymodel.h"

static const QStringList TROVE_LIST {
  "Switch puzzle",
  "Floor puzzle",
  "Escort gauntlet",
  "Trap gauntlet",
};

PlanSummaryModel::PlanSummaryModel(QObject* parent) : QObject(parent)
{
  m_rooms = 0;
  m_length = 0;
  m_argus = 0;
  m_troves = 0;
  m_darkshrines = 0;
  m_silverCaches = 0;
}

void PlanSummaryModel::loadFromData(const NavigationData& data)
{
  QList<RoomId> rooms;
  int argus = 0;
  int troves = 0;
  int darkshrines = 0;
  int silverCaches = 0;
  int unusedSilverKeys = 0;

  for (const auto& roomId: data.plannedRoute)
    if (roomId != "plaza" && !rooms.contains(roomId))
      rooms.append(roomId);

  for (const auto& roomId: rooms) {
    auto room = data.lab->getRoomFromId(roomId);

    for (const auto& content: room.contents) {
      if (content == "argus")
        argus += 1;
      if (content == "darkshrine")
        darkshrines += 1;
      if (content == "silver-key")
        unusedSilverKeys += 1;
      if (TROVE_LIST.contains(content))
        troves += 1;
    }

    for (const auto& content: room.contents)
      if (content == "silver-door" && unusedSilverKeys > 0) {
        silverCaches += 1;
        unusedSilverKeys -= 1;
      }
  }

  update_rooms(rooms.size() - 3); // exclude 3 trial rooms
  update_length(data.plannedRoute.size() - 1); // exclude plaza
  update_argus(argus);
  update_troves(troves);
  update_darkshrines(darkshrines);
  update_silverCaches(silverCaches);
}
