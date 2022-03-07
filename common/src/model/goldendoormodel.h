#ifndef GOLDENDOORMODEL_H
#define GOLDENDOORMODEL_H

#include "model/labyrinthdata.h"
#include "stdafx.h"

class GoldenDoorModel : public QAbstractListModel {
    Q_OBJECT

    enum Roles {
        CoordinateRole = Qt::UserRole + 1,
    };
    struct ModelData {
        QPoint coordinate;
    };

    QList<ModelData> d;

public:
    GoldenDoorModel(QObject* parent = nullptr);
    void loadFromData(const LabyrinthData& data);

public:
    int rowCount(const QModelIndex& parent = QModelIndex()) const;
    QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const;

protected:
    QHash<int, QByteArray> roleNames() const;
};

#endif // GOLDENDOORMODEL_H
