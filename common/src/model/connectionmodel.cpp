#include "stdafx.h"

#include "connectionmodel.h"

ConnectionModel::ConnectionModel()
{
}

void ConnectionModel::loadFromData(const LabyrinthData& lab, const NavigationData& navigation)
{
    beginResetModel();

    QSet<std::pair<QString, QString>> plannedConnections;
    for (int i = 0; i < navigation.plannedRoute.size() - 1; i++)
        plannedConnections.insert(std::pair<QString, QString>(navigation.plannedRoute[i], navigation.plannedRoute[i + 1]));

    d.clear();
    for (int i = 0; i < lab.rooms.size(); i++) {
        auto fromId = lab.rooms[i].id;
        for (int j = i + 1; j < lab.rooms.size(); j++) {
            auto toId = lab.rooms[j].id;
            if (lab.hasConnection(fromId, toId)) {
                ConnectionModelData modelData;
                modelData.fromRoom = lab.rooms[i].id;
                modelData.toRoom = lab.rooms[j].id;
                modelData.fromCoordinate = lab.rooms[i].coordinate;
                modelData.toCoordinate = lab.rooms[j].coordinate;
                modelData.isSecretPassage = !lab.hasDoorConnection(fromId, toId);
                modelData.isPlanned = plannedConnections.contains(std::pair<QString, QString>(fromId, toId)) || plannedConnections.contains(std::pair<QString, QString>(toId, fromId));
                d.append(modelData);
            }
        }
    }

    ConnectionModelData afterLastRoom;
    const auto& lastRoom = lab.rooms[lab.roomIdIndex[lab.sections[2].trialRoom]];
    afterLastRoom.fromCoordinate = lastRoom.coordinate;
    afterLastRoom.toCoordinate = lastRoom.coordinate + QPoint(300, 0);
    afterLastRoom.isSecretPassage = false;
    d.append(afterLastRoom);

    endResetModel();
}

void ConnectionModel::updateFromData(const NavigationData& data)
{
    QSet<std::pair<QString, QString>> plannedConnections;
    for (int i = 0; i < data.plannedRoute.size() - 1; i++)
        plannedConnections.insert(std::pair<QString, QString>(data.plannedRoute[i], data.plannedRoute[i + 1]));

    for (auto i = d.begin(); i != d.end(); i++) {
        i->isPlanned = plannedConnections.contains(std::pair<QString, QString>(i->fromRoom, i->toRoom)) || plannedConnections.contains(std::pair<QString, QString>(i->toRoom, i->fromRoom));
    }
    emit dataChanged(index(0), index(rowCount() - 1), { IsPlannedRole });
}

int ConnectionModel::rowCount(const QModelIndex& parent) const
{
    Q_UNUSED(parent)
    return d.size();
}

QVariant ConnectionModel::data(const QModelIndex& index, int role) const
{
    if (index.row() < 0 || index.row() >= rowCount())
        return QVariant();

    const auto& data = d[index.row()];
    switch (role) {
    case FromCoordinateRole:
        return data.fromCoordinate;
    case ToCoordinateRole:
        return data.toCoordinate;
    case IsSecretPassgeRole:
        return data.isSecretPassage;
    case IsPlannedRole:
        return data.isPlanned;
    default:
        return QVariant();
    }
}

QHash<int, QByteArray> ConnectionModel::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[FromCoordinateRole] = "fromCoordinate";
    roles[ToCoordinateRole] = "toCoordinate";
    roles[IsSecretPassgeRole] = "isSecretPassage";
    roles[IsPlannedRole] = "isPlanned";
    return roles;
}
