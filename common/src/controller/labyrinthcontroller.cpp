#include "stdafx.h"

#include "labyrinthcontroller.h"

LabyrinthController::LabyrinthController(ApplicationModel* model)
{
    this->model = model;
}

void LabyrinthController::importFile(const QString& file)
{
    qInfo() << "Import:" << file;

    if (model->loadFromFile(file)) {
        // update last loaded map date
        model->get_settings()->set_lastLoadedMapDate(model->labyrinthData.date);

        // copy the file to appdata directory
        const auto& appData = QDir(QStandardPaths::writableLocation(QStandardPaths::AppDataLocation));
        const auto& lastLoadedMap = appData.absoluteFilePath("lastLoaded.map");
        appData.mkpath(".");
        if (QFileInfo(file) != QFileInfo(lastLoadedMap)) {
            QFile::remove(lastLoadedMap);
            QFile::copy(file, lastLoadedMap);
        }
    }
}

void LabyrinthController::onRoomPresetSet(const QString& id, const QString& areaCode)
{
    auto& lab = model->labyrinthData;
    if (lab.roomIdIndex.contains(id)) {
        auto& room = lab.rooms[lab.roomIdIndex[id]];
        room.areaCode = areaCode;

        lab.normalizeDoorDirections(id);

        model->updateModelOnPresetChange();
    }
}
