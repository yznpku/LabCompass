#ifndef ROOMMODEL_H
#define ROOMMODEL_H

#include "model/labyrinthdata.h"
#include "model/navigationdata.h"
#include "stdafx.h"

struct RoomModelData {
    QString id;
    QString name;
    QPoint coordinate;
    QStringList contents;
    bool isTarget;
    bool isCurrent;
};
class RoomModel : public QAbstractListModel {
    Q_OBJECT

    enum Roles {
        IdRole = Qt::UserRole + 1,
        NameRole,
        CoordinateRole,
        ContentsRole,
        IsTargetRole,
        IsCurrentRole,
    };

    QList<RoomModelData> d;

public:
    RoomModel();
    void loadFromData(const LabyrinthData& lab, const NavigationData& navigation);
    void updateFromData(const NavigationData& data);

public:
    int rowCount(const QModelIndex& parent = QModelIndex()) const;
    QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const;

protected:
    QHash<int, QByteArray> roleNames() const;
};

#endif // ROOMMODEL_H
