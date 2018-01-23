#include "roommodel.h"

RoomModel::RoomModel()
{

}

void RoomModel::loadFromData(const LabyrinthData& lab, const NavigationData& navigation)
{
  beginResetModel();

  d.clear();
  foreach (const auto& room, lab.rooms) {
    RoomModelData modelData;
    modelData.id = room.id;
    modelData.name = room.name;
    modelData.coordinate = room.coordinate;
    modelData.contents = room.contents;

    if (lab.roomIsTrial(room.id)) {
      modelData.contents.append(lab.weapon);
      if (lab.sections[0].trialRoom == room.id)
        modelData.contents.append(lab.sectionMechanics[0]);
      if (lab.sections[1].trialRoom == room.id)
        modelData.contents.append(lab.sectionMechanics[1]);
      if (lab.sections[2].trialRoom == room.id)
        modelData.contents.append(lab.traps);
    }

    modelData.isTarget = navigation.targetRooms.contains(room.id);
    modelData.isCurrent = navigation.currentRoom == room.id;

    d.append(modelData);
  }

  endResetModel();
}

void RoomModel::updateFromData(const NavigationData& data)
{
  for (auto i = d.begin(); i != d.end(); i++) {
    i->isTarget = data.targetRooms.contains(i->id);
    i->isCurrent = data.currentRoom == i->id;
  }
  emit dataChanged(index(0), index(rowCount() - 1), {IsTargetRole, IsCurrentRole});
}

int RoomModel::rowCount(const QModelIndex& parent) const
{
  Q_UNUSED(parent)
  return d.size();
}

QVariant RoomModel::data(const QModelIndex& index, int role) const
{
  if (index.row() < 0 || index.row() >= rowCount())
    return QVariant();

  const auto& data = d[index.row()];
  switch (role) {
  case IdRole:
    return data.id;
  case NameRole:
    return data.name;
  case CoordinateRole:
    return data.coordinate;
  case ContentsRole:
    return data.contents;
  case IsTargetRole:
    return data.isTarget;
  case IsCurrentRole:
    return data.isCurrent;
  default:
    return QVariant();
  }
}

QHash<int, QByteArray> RoomModel::roleNames() const
{
  QHash<int, QByteArray> roles;
  roles[IdRole] = "id";
  roles[NameRole] = "name";
  roles[CoordinateRole] = "coordinate";
  roles[ContentsRole] = "contents";
  roles[IsTargetRole] = "isTarget";
  roles[IsCurrentRole] = "isCurrent";
  return roles;
}
