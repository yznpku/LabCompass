#include "navigationdata.h"

void NavigationData::loadFromData(const LabyrinthData* lab, const PlanData& plan)
{
  this->lab = lab;

  currentRoomDetermined = true;
  currentRoom = "plaza";
  possibleCurrentRooms = {"plaza"};

  foreach (const auto& room, lab->rooms)
    if (room.contents.contains("golden-key"))
      contentState.goldenKeyLocations.append(room.id);
  contentState.lockedDoors = lab->goldenDoors;

  targetRooms = plan.targetRooms;
}

void NavigationData::updatePlannedRouteAndInstructions()
{
  if (!currentRoomDetermined) {
    plannedRoute = {};
    return;
  }

  QList<RoomId> newPlannedRoute;
  ContentState tempGolden = contentState;

  int startSection = lab->getRoomFromId(currentRoom).section;
  if (startSection == -1) {
    newPlannedRoute.append("plaza");

  } else {
    auto begin = currentRoom;
    auto end = lab->sections[startSection].trialRoom;
    newPlannedRoute.append(plannedRouteInsideSection(startSection, begin, end, targetRooms, &tempGolden));
  }

  for (int i = startSection + 1; i < 3; i++) {
    auto begin = i == startSection ? currentRoom : lab->sections[i].firstRoom;
    auto end = lab->sections[i].trialRoom;
    newPlannedRoute.append(plannedRouteInsideSection(i, begin, end, targetRooms, &tempGolden));
  }

  plannedRoute = newPlannedRoute;
}

QList<RoomId> NavigationData::plannedRouteInsideSection(int section, const RoomId& begin, const RoomId& end, const QList<RoomId>& targetRooms, ContentState* tempGolden)
{
  QList<RoomId> sectionTargetRooms;
  std::copy_if(targetRooms.constBegin(), targetRooms.constEnd(), std::back_inserter(sectionTargetRooms),
               [this, section](const RoomId& room) { return lab->sections[section].roomIds.contains(room); });

  if (tempGolden->goldenKeyLocations.contains(begin)) {
    tempGolden->goldenKeyLocations.removeAll(begin);
    tempGolden->goldenKeysInInventory += 1;
  }

  if (begin == end && std::count_if(sectionTargetRooms.constBegin(), sectionTargetRooms.constEnd(),
                                    [begin](const RoomId& target) { return target == begin; }) == sectionTargetRooms.size())
    return {begin};

  struct State {
    ContentState contentState;
    RoomId currentRoom;
    QList<RoomId> history;
    qreal length;
  };
  auto cmp = [](const State& o1, const State& o2) { return o1.length > o2.length; };

  std::priority_queue<State, std::vector<State>, decltype(cmp)> queue(cmp);
  State initialState {*tempGolden, begin, {begin}, 0};
  queue.push(initialState);

  while (!queue.empty()) {
    State state = queue.top();
    queue.pop();

    auto connections = lab->connections[state.currentRoom];
    for (auto i = connections.constBegin(); i != connections.constEnd(); i++)
      if (!i.value().isEmpty() && lab->sections[section].roomIds.contains(i.key())) {
        auto roomId = i.key();
        State newState = state;
        newState.currentRoom = roomId;
        newState.history.append(roomId);
        newState.length += lab->roomCost(roomId);

        if (state.contentState.lockedDoors.contains(std::pair<RoomId, RoomId>(state.currentRoom, roomId)) ||
            state.contentState.lockedDoors.contains(std::pair<RoomId, RoomId>(roomId, state.currentRoom))) {
          if (state.contentState.goldenKeysInInventory < 1)
            continue;
          newState.contentState.goldenKeysInInventory -= 1;
          newState.contentState.lockedDoors.removeAll(std::pair<RoomId, RoomId>(state.currentRoom, roomId));
          newState.contentState.lockedDoors.removeAll(std::pair<RoomId, RoomId>(roomId, state.currentRoom));
        }

        if (state.contentState.goldenKeyLocations.contains(roomId)) {
          newState.contentState.goldenKeyLocations.removeAll(roomId);
          newState.contentState.goldenKeysInInventory += 1;
        }

        if (newState.currentRoom == end && listContainsAll(newState.history, sectionTargetRooms)) {
          *tempGolden = newState.contentState;
          return newState.history;
        }

        queue.push(newState);
      }
  }

  return {};
}

bool NavigationData::listContainsAll(const QStringList& l1, const QStringList& l2)
{
  foreach (auto& l, l2)
    if (!l1.contains(l))
      return false;
  return true;
}
