#ifndef INSTRUCTIONMODEL_H
#define INSTRUCTIONMODEL_H

#include "global.h"
#include "model/navigationdata.h"

class InstructionModel : public QObject {
    Q_OBJECT

    QML_READONLY_VAR_PROPERTY(QVariantMap, preset) // Preset
    QML_READONLY_VAR_PROPERTY(QStringList, roomLoot)
    QML_READONLY_VAR_PROPERTY(QVariantList, doorExitLocations) // DoorExitLocationModel
    QML_READONLY_VAR_PROPERTY(QVariantList, contentLocations) // ContentLocationModel
    QML_READONLY_VAR_PROPERTY(bool, roomHasPortal)

    QML_READONLY_VAR_PROPERTY(bool, hasNextRoom)
    QML_READONLY_VAR_PROPERTY(bool, atTrialRoom)
    QML_READONLY_VAR_PROPERTY(bool, nextRoomIsPreviousRoom)
    QML_READONLY_VAR_PROPERTY(bool, nextRoomIsUnmarkedOppositeDirection)
    QML_READONLY_VAR_PROPERTY(QString, nextRoomName)
    QML_READONLY_VAR_PROPERTY(QString, nextRoomConnectionType) // "none" | "door" | "secret"
    QML_READONLY_VAR_PROPERTY(QString, nextRoomDirection)

    QML_READONLY_VAR_PROPERTY(int, finishedSections)
    QML_READONLY_VAR_PROPERTY(int, currentSection)
    QML_READONLY_VAR_PROPERTY(bool, shouldKillIzaro)
    QML_READONLY_VAR_PROPERTY(QString, izaroMechanics)

public:
    InstructionModel(QObject* parent = nullptr);
    void loadFromData(const NavigationData& data);

private:
    void updateRoomPreset(const NavigationData& data);
    void updateExitLocations(const NavigationData& data);
    void updateContentsAndLocations(const NavigationData& data);

    QRectF getTileRect(const QString& direction, const QVariantMap& preset) const;
};

#endif // INSTRUCTIONMODEL_H
