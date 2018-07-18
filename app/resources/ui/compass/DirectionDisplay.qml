import QtQuick 2.8
import com.labcompass 1.0
import '..'

Item {
  id: root
  property var instructionModel

  Item {
    anchors.centerIn: parent

    Repeater {
      id: exitDirectionView
      model: instructionModel.doorExitLocations
      anchors.centerIn: parent

      Rectangle {
        x: Global.directionMapping[modelData.direction].dx * 48 - width / 2
        y: Global.directionMapping[modelData.direction].dy * 48 - height / 2
        width: 16
        height: 16
        radius: 8
        color: modelData.direction === instructionModel.nextRoomDirection ? Global.activePathColor : '#909090'
        border {
          width: 1
          color: 'black'
        }
      }
    }

    Repeater {
      id: contentLocationsView
      model: instructionModel.contentLocations

      Rectangle {
        x: Global.directionMapping[modelData.direction].dx * 30 - width / 2
        y: Global.directionMapping[modelData.direction].dy * 30 - height / 2
        width: 10
        height: 10
        radius: 5
        color: instructionModel.nextRoomConnectionType === 'secret' && !modelData.major ? Global.activePathColor : 'white'
        border {
          width: 1
          color: 'black'
        }
      }
    }

    RoomContentView {
      anchors.centerIn: parent
      model: instructionModel.roomLoot
    }
  }
}
