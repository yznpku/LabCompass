#include "directionnormalizer.h"

static const QList<DirectionCode> REGULAR_DIRECTION_LIST {"N", "NE", "E", "SE", "S", "SW", "W", "NW"};

DirectionNormalizer::DirectionNormalizer()
{

}

RoomConnections DirectionNormalizer::normalize(const RoomConnections& original, const QList<DirectionCode>& pattern)
{
  auto breakdown = breakdownConnections(original);

  auto regularCount = breakdown.regularDirectionRooms.size();
  auto unknownCount = breakdown.unknownDirectionRooms.size();
  auto patternSize = pattern.size();

  // normalize regular directions
  if (regularCount) {
    QVector<QVector<double>> costMatrix(regularCount, QVector<double>(patternSize, 0));
    for (auto i = 0; i < regularCount; i++)
      for (auto j = 0; j < patternSize; j++)
        costMatrix[i][j] = costBetweenDirections(breakdown.regularDirectionRooms[i].first, pattern[j]);

    QVector<int> assignment;
    hungarian.Solve(costMatrix, assignment);
    for (int i = 0; i < regularCount; i++)
      breakdown.regularDirectionRooms[i].first = pattern[assignment[i]];
  }

  // predict the last unknown direction
  if (unknownCount == 1 && unknownCount + regularCount == patternSize) {
    auto unusedList = pattern;
    foreach (const auto& i, breakdown.regularDirectionRooms)
      unusedList.removeOne(i.first);

    const auto& unusedDirection = unusedList[0];
    const auto& unusedRoom = breakdown.unknownDirectionRooms[0];

    breakdown.unknownDirectionRooms.clear();
    breakdown.regularDirectionRooms.append({unusedDirection, unusedRoom});
  }

  return reconstructConnections(breakdown);
}

DirectionNormalizer::ConnectionDetails DirectionNormalizer::breakdownConnections(const RoomConnections& connections)
{
  ConnectionDetails breakdown;

  for (auto i = connections.constBegin(); i != connections.constEnd(); i++) {
    const auto& room = i.key();
    const auto& list = i.value();

    breakdown.rooms.append(room);

    for (auto j = list.constBegin(); j != list.constEnd(); j++) {
      const auto& direction = *j;

      if (direction.isEmpty())
        breakdown.unknownDirectionRooms.append(room);

      if (direction == "C")
        breakdown.secretPassageRooms.append(room);

      if (REGULAR_DIRECTION_LIST.contains(direction))
        breakdown.regularDirectionRooms.append({direction, room});
    }
  }

  return breakdown;
}

RoomConnections DirectionNormalizer::reconstructConnections(const DirectionNormalizer::ConnectionDetails& breakdown)
{
  RoomConnections connections;

  foreach (const auto& room, breakdown.rooms)
    connections.insert(room, {});

  foreach (const auto& i, breakdown.regularDirectionRooms) {
    const auto& direction = i.first;
    const auto& room = i.second;
    connections[room].append(direction);
  }

  foreach (const auto& room, breakdown.secretPassageRooms)
    connections[room].append("C");

  foreach (const auto& room, breakdown.unknownDirectionRooms)
    connections[room].append("");

  return connections;
}

qreal DirectionNormalizer::costBetweenDirections(const DirectionCode& d1, const DirectionCode& d2)
{
  int i1 = REGULAR_DIRECTION_LIST.indexOf(d1);
  int i2 = REGULAR_DIRECTION_LIST.indexOf(d2);

  auto diff = abs(i1 - i2) <= 4 ? abs(i1 - i2) : 8 - abs(i1 - i2);
  return diff * diff;
}
