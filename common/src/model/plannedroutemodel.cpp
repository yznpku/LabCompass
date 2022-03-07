#include "stdafx.h"

#include "plannedroutemodel.h"

PlannedRouteModel::PlannedRouteModel()
{
}

void PlannedRouteModel::loadFromData(const NavigationData& data)
{
    beginResetModel();

    d.clear();
    foreach (auto& id, data.plannedRoute) {
        if (id != "plaza") {
            ModelData modelData;
            modelData.id = id;
            d.append(modelData);
        }
    }

    endResetModel();
}

int PlannedRouteModel::rowCount(const QModelIndex& parent) const
{
    Q_UNUSED(parent)
    return d.size();
}

QVariant PlannedRouteModel::data(const QModelIndex& index, int role) const
{
    if (index.row() < 0 || index.row() >= rowCount()) {
        return QVariant();
    }

    const auto& data = d[index.row()];
    switch (role) {
    case IdRole:
        return data.id;
    default:
        return QVariant();
    }
}

QHash<int, QByteArray> PlannedRouteModel::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[IdRole] = "id";
    return roles;
}
