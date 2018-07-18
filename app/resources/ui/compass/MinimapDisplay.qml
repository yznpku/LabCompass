import QtQuick 2.8
import com.labcompass 1.0
import '../point.js' as Point
import '..'

Item {
  id: root
  property var instructionModel

  SvgImage {
    anchors.fill: parent
    source: 'qrc:/images/room-preset/tile/' + instructionModel.preset.keyword + '.svg'
  }

  Repeater {
    id: exitDirectionView
    model: instructionModel.doorExitLocations

    SvgImage {
      x: modelData.tileRect.x * root.width
      y: modelData.tileRect.y * root.height
      width: modelData.tileRect.width * root.width
      height: modelData.tileRect.height * root.height
      source: modelData.direction === instructionModel.nextRoomDirection ? 'qrc:/images/compass/door-target.svg'
                                                                         : 'qrc:/images/compass/door-normal.svg'
    }
  }

  Repeater {
    id: contentLocationsView
    model: instructionModel.contentLocations

    SvgImage {
      x: modelData.tileRect.x * root.width
      y: modelData.tileRect.y * root.height
      width: modelData.tileRect.width * root.width
      height: modelData.tileRect.height * root.height
      source: instructionModel.nextRoomConnectionType === 'secret' && !modelData.major ? 'qrc:/images/compass/loot-active.svg'
                                                                                       : 'qrc:/images/compass/loot-normal.svg'
    }
  }

  RoomContentView {
    anchors.bottom: parent.bottom
    model: instructionModel.roomLoot
  }
}
