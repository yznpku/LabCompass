#ifndef CONNECTIONMODEL_H
#define CONNECTIONMODEL_H

#include "model/labyrinthdata.h"
#include "model/listmodel.h"
#include "model/navigationdata.h"
#include "stdafx.h"

struct ConnectionModelData {
    QString fromRoom;
    QString toRoom;
    QPoint fromCoordinate;
    QPoint toCoordinate;
    bool isSecretPassage { false };
    bool isPlanned { false };
};

class ConnectionModel : public ListModel {
    Q_OBJECT

    QList<ConnectionModelData> d;
    enum Roles {
        FromCoordinateRole = Qt::UserRole + 1,
        ToCoordinateRole,
        IsSecretPassgeRole,
        IsPlannedRole,
    };

public:
    ConnectionModel();
    void loadFromData(const LabyrinthData& data, const NavigationData& navigation);
    void updateFromData(const NavigationData& data);

public:
    int rowCount(const QModelIndex& parent = QModelIndex()) const;
    QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const;

protected:
    QHash<int, QByteArray> roleNames() const;
};

#endif // CONNECTIONMODEL_H
