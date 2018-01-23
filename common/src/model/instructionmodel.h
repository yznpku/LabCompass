#ifndef INSTRUCTIONMODEL_H
#define INSTRUCTIONMODEL_H

#include "stdafx.h"
#include "model/navigationdata.h"

class InstructionModel : public QObject
{
  Q_OBJECT

  QML_READONLY_VAR_PROPERTY(QStringList, roomLoot)
  QML_READONLY_VAR_PROPERTY(QStringList, roomDoorExitDirections)
  QML_READONLY_VAR_PROPERTY(bool, roomHasPortal)

  QML_READONLY_VAR_PROPERTY(bool, hasNextRoom)
  QML_READONLY_VAR_PROPERTY(bool, atPlaza)
  QML_READONLY_VAR_PROPERTY(bool, atTrialRoom)
  QML_READONLY_VAR_PROPERTY(bool, nextRoomIsPreviousRoom)
  QML_READONLY_VAR_PROPERTY(bool, nextRoomIsUnmarkedOppositeDirection)
  QML_READONLY_VAR_PROPERTY(QString, nextRoomName)
  QML_READONLY_VAR_PROPERTY(QString, nextRoomConnectionType) // values: "none", "door", "secret", "portal"
  QML_READONLY_VAR_PROPERTY(QString, nextRoomDirection)

  QML_READONLY_VAR_PROPERTY(int, finishedSections)
  QML_READONLY_VAR_PROPERTY(int, currentSection)
  QML_READONLY_VAR_PROPERTY(bool, shouldKillIzaro)
  QML_READONLY_VAR_PROPERTY(QString, izaroMechanics)

public:
  InstructionModel(QObject* parent = nullptr);
  void loadFromData(const NavigationData& data);
};

#endif // INSTRUCTIONMODEL_H
