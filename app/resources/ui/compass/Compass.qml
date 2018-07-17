import QtQuick 2.8
import com.labcompass 1.0
import '..'

Item {
  id: root

  width: 170
  height: 170

  Item {
    id: directionDisplay
    width: 170
    height: 170

    SvgImage {
      anchors.fill: parent
      source: 'qrc:/images/compass/direction-hud.svg'
    }

    Loader {
      anchors.fill: parent
      active: Global.model.inLab && Global.model.currentRoomDetermined
      sourceComponent: DirectionDisplay {
        instructionModel: Global.model.instructionModel
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
