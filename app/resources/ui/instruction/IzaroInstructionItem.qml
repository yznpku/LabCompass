import QtQuick 2.8
import com.labcompass 1.0
import '..'

InstructionItem {
  id: root

  property string mechanics

  Text {
    text: 'Defeat Izaro'
    color: Global.primaryTextColor
  }
  Row {
    visible: mechanics
    spacing: 4
    SvgImage {
      source: 'qrc:/images/instruction/mechanics.svg'
    }
    Text {
      text: mechanics in Global.nameMapping ? Global.nameMapping[mechanics] : mechanics
      color: Global.primaryTextColor
    }
  }

  iconComponent: Item {
    id: izaroInstructionItemIcon
    objectName: 'izaroInstructionItemIcon'

    SvgImage {
      anchors.centerIn: parent
      visible: izaroInstructionItemIcon.state === ''
      source: root.mechanics === 'ChargeDisruptors' || root.mechanics === 'Idols' ? 'qrc:/images/instruction/izaro-wait.svg'
                                                                                  : 'qrc:/images/instruction/izaro-kill.svg'
      width: 20
      height: 20
    }

    property real countdownStart: 0
    property real countdownEnd: 0
    property real currentTime: 0
    CircleProgressBar {
      anchors.centerIn: parent
      visible: izaroInstructionItemIcon.state === 'countdownRunning'
      width: 30
      height: 30
      color: '#FDD835'
      circleWidth: 2
      value: (countdownEnd - currentTime) / (countdownEnd - countdownStart)
      Text {
        anchors.centerIn: parent
        text: Math.ceil((countdownEnd - currentTime) / 1000)
        color: '#FDD835'
        font.family: 'Open Sans'
        font.pixelSize: 14
      }
    }
    Timer {
      running: izaroInstructionItemIcon.state === 'countdownRunning'
      interval: 50
      repeat: true
      triggeredOnStart: true
      onTriggered: {
        currentTime = Date.now();
        if (currentTime > countdownEnd)
          izaroInstructionItemIcon.state = 'countdownFinished';
      }
    }

    SvgImage {
      anchors.centerIn: parent
      visible: izaroInstructionItemIcon.state === 'countdownFinished'
      source: 'qrc:/images/instruction/izaro-kill.svg'
      width: 20
      height: 20

      SequentialAnimation on opacity {
        loops: Animation.Infinite
        running: true
        NumberAnimation { from: 1; to: 0; duration: 200; easing.type: Easing.InQuad }
        NumberAnimation { from: 0; to: 1; duration: 200; easing.type: Easing.OutQuad }
      }
    }

    states: [
      State {
        name: 'countdownRunning'
        StateChangeScript {
          script: {
            if (!(root.mechanics === 'ChargeDisruptors' || root.mechanics === 'Idols'))
              return;

            var delay = root.mechanics === 'ChargeDisruptors' ? 29 : 27;
            countdownStart = Date.now();
            countdownEnd = countdownStart + delay * 1000;
            currentTime = countdownStart;
          }
        }
      },
      State { name: 'countdownFinished' }
    ]

    function onIzaroBattleStarted() {
      if (root.mechanics === 'ChargeDisruptors' || root.mechanics === 'Idols')
        state = 'countdownRunning';
    }
  }
}
