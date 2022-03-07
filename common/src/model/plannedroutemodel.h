#ifndef PLANNEDROUTEMODEL_H
#define PLANNEDROUTEMODEL_H

#include "model/navigationdata.h"
#include "stdafx.h"

class PlannedRouteModel : public QAbstractListModel {
    Q_OBJECT

    enum Roles {
        IdRole = Qt::UserRole + 1,
    };
    struct ModelData {
        QString id;
    };

    QList<ModelData> d;

public:
    PlannedRouteModel();
    void loadFromData(const NavigationData& data);

public:
    int rowCount(const QModelIndex& parent = QModelIndex()) const;
    QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const;

protected:
    QHash<int, QByteArray> roleNames() const;
};

#endif // PLANNEDROUTEMODEL_H
