import QtQuick 2.8

Image {
  property var direction: {'N': [0, -1], 'NE': [0.71, -0.71], 'E': [1, 0], 'SE': [0.71, 0.71], 'S': [0, 1], 'SW': [-0.71, 0.71], 'W': [-1, 0], 'NW': [-0.71, -0.71]}
  property alias exitDirectionModel: exitDirectionView.model
  property alias contentDirectionModel: contentDirectionView.model
  property alias contentModel: contentView.model
  property string planDirection

  source: '../images/hud.png'



  Repeater {
    id: exitDirectionView
    Rectangle {
      x: 56 + direction[modelData][0] * 48
      y: 56 + direction[modelData][1] * 48
      width: 16
      height: 16
      radius: 8
      color: modelData == planDirection ? 'gold' : 'skyblue'
      border {
        width: 1
        color: 'black'
      }
    }
  }

  Repeater {
    id: contentDirectionView
    Rectangle {
      x: 59 + direction[modelData][0] * 32
      y: 59 + direction[modelData][1] * 32
      width: 10
      height: 10
      radius: 5
      color: 'white'
      border {
        width: 1
        color: 'black'
      }
    }
  }

  Row {
    anchors.centerIn: parent
    spacing: 2
    Repeater {
      id: contentView
      Image {
        source: '../images/lab-content/' + modelData + '.png'
      }
    }
  }

  Rectangle {
    id: timerView
    color: '#88000000'
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
