import QtQuick 2.8
import com.labcompass 1.0
import '..'

Item {
  id: root

  width: 210
  height: 170

  property bool displayActive: Global.model.inLab && Global.model.currentRoomDetermined
  property bool useMinimapDisplay: Global.model.settings.showMinimap && displayActive && Object.keys(Global.model.instructionModel.preset).length

  Item {
    id: directionDisplay
    width: 170
    height: 170
    anchors.right: parent.right
    visible: !useMinimapDisplay

    SvgImage {
      anchors.fill: parent
      source: 'qrc:/images/compass/direction-hud.svg'
    }

    Loader {
      anchors.fill: parent
      active: !useMinimapDisplay && displayActive
      sourceComponent: DirectionDisplay {
        instructionModel: Global.model.instructionModel
      }
    }
  }

  Item {
    id: minimapDisplay
    anchors.fill: parent
    visible: useMinimapDisplay

    SvgImage {
      anchors.fill: parent
      source: 'qrc:/images/compass/minimap-hud.svg'
    }

    Loader {
      width: 182
      height: 140
      anchors.centerIn: parent
      active: useMinimapDisplay
      sourceComponent: MinimapDisplay {
        instructionModel: Global.model.instructionModel
      }
    }
  }

  Rectangle {
    id: timerView
    color: '#88000000'
    x: 150
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
