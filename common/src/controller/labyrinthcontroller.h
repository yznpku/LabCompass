#ifndef LABYRINTHCONTROLLER_H
#define LABYRINTHCONTROLLER_H

#include "model/applicationmodel.h"

class LabyrinthController : public QObject {
    Q_OBJECT

    ApplicationModel* model;

public:
    LabyrinthController(ApplicationModel* model);

public slots:
    void importFile(const QString& file);
    void onRoomPresetSet(const QString& id, const QString& areaCode);
};

#endif // LABYRINTHCONTROLLER_H
