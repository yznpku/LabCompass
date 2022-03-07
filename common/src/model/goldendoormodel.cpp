#include "stdafx.h"

#include "goldendoormodel.h"

GoldenDoorModel::GoldenDoorModel(QObject* parent)
    : QAbstractListModel(parent)
{
}

void GoldenDoorModel::loadFromData(const LabyrinthData& data)
{
    beginResetModel();

    d.clear();
    foreach (auto& door, data.goldenDoors) {
        ModelData modelData;
        auto room1 = data.getRoomFromId(door.first);
        auto room2 = data.getRoomFromId(door.second);
        modelData.coordinate = (room1.coordinate + room2.coordinate) / 2;
        d.append(modelData);
    }

    endResetModel();
}

int GoldenDoorModel::rowCount(const QModelIndex& parent) const
{
    Q_UNUSED(parent)
    return d.size();
}

QVariant GoldenDoorModel::data(const QModelIndex& index, int role) const
{
    if (index.row() < 0 || index.row() >= rowCount())
        return QVariant();

    const auto& data = d[index.row()];
    switch (role) {
    case CoordinateRole:
        return data.coordinate;
    default:
        return QVariant();
    }
}

QHash<int, QByteArray> GoldenDoorModel::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[CoordinateRole] = "coordinate";
    return roles;
}
