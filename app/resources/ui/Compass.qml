import QtQuick 2.8
import com.labcompass 1.0

Image {
  id: root

  property var instructionModel: Global.model.instructionModel
  property bool valid: Global.model.inLab && Global.model.currentRoomDetermined

  source: 'qrc:/images/hud.png'

  Item {
    visible: valid

    Repeater {
      id: exitDirectionView
      model: instructionModel.roomDoorExitDirections

      Rectangle {
        x: 77 + Global.directionMapping[modelData].dx * 48
        y: 77 + Global.directionMapping[modelData].dy * 48
        width: 16
        height: 16
        radius: 8
        color: modelData === instructionModel.nextRoomDirection ? Global.activePathColor : '#909090'
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
        x: 80 + Global.directionMapping[modelData.direction].dx * 30
        y: 80 + Global.directionMapping[modelData.direction].dy * 30
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
  }

  Row {
    anchors.centerIn: parent
    spacing: 2
    visible: valid

    Repeater {
      id: contentView
      model: instructionModel.roomLoot

      SvgImage {
        source: modelData in Global.contentIconMapping ? 'qrc:/images/lab-content/' + Global.contentIconMapping[modelData] + '.svg' : ''
      }
    }
  }

  Rectangle {
    id: timerView
    color: '#88000000'
    x: 110
    y: 10
    width: 50
    height: 20
    visible: false
    Text {
      id: timerViewText
      anchors.centerIn: parent
      text: '00:00'
      color: 'white'
    }
    Timer {
      id: timer
      property var startTime
      interval: 100
      repeat: true
      triggeredOnStart: true
      onTriggered: {
        var elapsed = Date.now() - timer.startTime;
        timerViewText.text = ('00'+Math.floor(elapsed/60000)).slice(-2) + ':' + ('00'+Math.floor(elapsed%60000/1000)).slice(-2);
      }
    }
  }

  function restartTimer() {
    timer.startTime = Date.now();
    timer.restart();
    timerView.visible = true;
  }
  function stopTimer() {
    timer.stop();
  }
  function closeTimer() {
    stopTimer();
    timerView.visible = false;
  }
}
