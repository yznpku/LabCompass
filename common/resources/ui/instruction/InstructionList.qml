import QtQuick 2.8
import com.labcompass 1.0

Column {
  id: root

  property bool inLab: Global.model.inLab
  property bool currentRoomDetermined: Global.model.currentRoomDetermined
  property bool valid: inLab && currentRoomDetermined
  property var instructionModel: Global.model.instructionModel

  WarningInstructionItem {
    visible: !Global.model.logFileOpen
    text: 'Unable to locate PoE installation.\n\nYou can try to:\n- run PoE client\n- set the path in Options window.'
  }

  WarningInstructionItem {
    visible: inLab && !currentRoomDetermined
    text: 'Unable to determine your location.\n\n- Open Planner window and click on your current room.'
  }

  IzaroInstructionItem {
    visible: valid &&
             instructionModel.atTrialRoom &&
             instructionModel.shouldKillIzaro &&
             instructionModel.finishedSections <= instructionModel.currentSection
    mechanics: instructionModel.izaroMechanics
  }

  DirectionInstructionItem {
    visible: valid &&
             instructionModel.hasNextRoom &&
             (connectionType === 'door' || connectionType === 'secret') &&
             (!instructionModel.atTrialRoom || !instructionModel.shouldKillIzaro || instructionModel.finishedSections > instructionModel.currentSection)
    connectionType: instructionModel.nextRoomConnectionType
    direction: instructionModel.nextRoomDirection
    nextRoomName: instructionModel.nextRoomName
    atPlaza: instructionModel.atPlaza
    nextRoomIsPreviousRoom: instructionModel.nextRoomIsPreviousRoom
    nextRoomIsUnmarkedOppositeDirection: instructionModel. nextRoomIsUnmarkedOppositeDirection
  }

  LootInstructionItem {
    visible: valid && instructionModel.roomLoot.length
    model: instructionModel.roomLoot
  }

  Item { width: 1; height: 1 }
}
