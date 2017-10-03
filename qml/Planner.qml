import QtQuick 2.8
import QtGraphicalEffects 1.0
import com.labcompass 1.0

Rectangle {
  id: root
  property alias roomModel: roomView.model
  property var linkModel: []
  property var plan: []
  property int planRooms: 0
  property int planLength: 0
  property int planGPs: 0
  property int planArgus: 0
  property int planDarkshrines: 0
  property int planSilverKeys: 0
  property int planSilverDoors: 0

  signal back
  signal reset
  signal move(int moveTo)

  width: 1000
  height: 338
  color: '#DDCCFF00'

  onLinkModelChanged: linkView.requestPaint()

  Grid {
    columns: 2
    padding: 20
    spacing: 10

    Rectangle {
      id: labMap
      width: 830
      height: 260
      color: '#DD223300'
      clip: true

      Canvas {
        id: linkView
        anchors.fill: parent
        onPaint: {
          var ctx = linkView.getContext('2d');

          for (var i = 0; i < linkModel.length; i++) {
            var link = linkModel[i];
            if (link.secret) {
              ctx.lineWidth = 2;
              ctx.strokeStyle = '#44F0FFF0';
            }
            else {
              ctx.lineWidth = 4;
              ctx.strokeStyle = '#BBF0FFF0';
            }
            ctx.beginPath();
            ctx.moveTo(link.x1, link.y1);
            ctx.lineTo(link.x2, link.y2);
            ctx.stroke();
          }
        }
      }

      Repeater {
        id: roomView

        Item {
          x: modelData.x - 24
          y: modelData.y - 24
          width: 48
          height: 48
          visible: !modelData.invalid

          MouseArea {
            anchors.fill: parent
            cursorShape: Qt.PointingHandCursor
            onClicked: move(index)
          }

          RectangularGlow {
            opacity: plan.indexOf(index) >= 0 ? 1 : 0
            anchors.fill: rect
            glowRadius: 4
            spread: 0.6
            color: "white"
            cornerRadius: 24
          }

          Rectangle {
            id: rect
            anchors.fill: parent
            visible: false
            radius: 24
            color: modelData.trial ? 'khaki' : 'yellowgreen'
          }

          DropShadow {
            anchors.fill: rect
            source: rect
            verticalOffset: 2
            radius: 4.0
            samples: 8
            color: '#80000000'
          }

          Row {
            id: contents
            visible: false
            anchors.centerIn: parent
            spacing: 2
            Repeater {
              model: modelData['contents']
              Image {
                source: '../images/lab-content/' + modelData + '.png'
              }
            }
          }

          DropShadow {
            anchors.fill: contents
            source: contents
            verticalOffset: 1
            radius: 2.0
            samples: 8
            color: '#80000000'
          }

          Rectangle {
            anchors.right: parent.right
            anchors.bottom: parent.bottom
            width: 16
            height: 16
            radius: 8
            color: '#80000000'

            Text {
              anchors.centerIn: parent
              text: index
              color: 'white'
              font.family: 'consolas'
            }
          }
        }
      }

      Image {
        property int markerPos: plan && plan.length > 0 ? plan[plan.length - 1] : 0
        x: (markerPos == 0 ? -20 : roomModel[markerPos].x) - 18
        y: (markerPos == 0 ? 129 : roomModel[markerPos].y) - 32
        source: '../images/map-marker.png'

        Behavior on x {
          NumberAnimation {
            duration: 100
            easing.type: Easing.OutCubic
          }
        }
        Behavior on y {
          NumberAnimation {
            duration: 100
            easing.type: Easing.OutCubic
          }
        }
      }
    }

    Rectangle {
      width: 120
      height: 260
      color: '#DD223300'
      Grid {
        anchors.horizontalCenter: parent.horizontalCenter
        horizontalItemAlignment: Grid.AlignHCenter
        padding: 10
        spacing: 10
        columns: 1
        Text {
          text: 'SUMMARY'
          font.pointSize: 16
          color: 'white'
        }
        Grid {
          spacing: 10
          columns: 3
          horizontalItemAlignment: Grid.AlignHCenter
          verticalItemAlignment: Grid.AlignVCenter
          Text { color: 'white'; text: 'Rooms' }
          Item { width: 1; height: 1 }
          Text { color: 'white'; text: planRooms }
          Text { color: 'white'; text: 'Length' }
          Item { width: 1; height: 1 }
          Text { color: 'white'; text: planLength }
          Image { source: '../images/lab-content/argus.png' }
          Text { color: 'white'; text: '✕' }
          Text { color: 'white'; text: planArgus }
          Row {
            Image { source: '../images/lab-content/gauntlet.png' }
            Image { source: '../images/lab-content/puzzle.png' }
          }
          Text { color: 'white'; text: '✕' }
          Text { color: 'white'; text: planGPs }
          Image { source: '../images/lab-content/darkshrine.png' }
          Text { color: 'white'; text: '✕' }
          Text { color: 'white'; text: planDarkshrines }
          Image { source: '../images/lab-content/silver-key.png' }
          Text { color: 'white'; text: '✕' }
          Text { color: 'white'; text: planSilverKeys }
          Image { source: '../images/lab-content/silver-door.png' }
          Text { color: 'white'; text: '✕' }
          Text { color: 'white'; text: planSilverDoors }
        }
      }
    }

    Row {
      spacing: 4
      Rectangle {
        width: 80
        height: 28
        color: '#DD223300'
        Text {
          anchors.centerIn: parent
          text: 'Plan:'
          color: 'white'
          font.pointSize: 16
        }
      }
      Repeater {
        id: planView
        model: plan
        Rectangle {
          width: 28
          height: 28
          color: '#DD223300'
          Text {
            anchors.centerIn: parent
            text: modelData
            color: 'white'
            font.pointSize: 12
          }
        }
      }
    }

    Row {
      spacing: 9
      Rectangle {
        width: 34
        height: 28
        color: '#DD223300'
        Image {
          anchors.centerIn: parent
          source: '../images/backspace.png'
        }
        MaterialInk {
          anchors.fill: parent
          onClicked: back()
        }
      }
      Rectangle {
        width: 34
        height: 28
        color: '#DD223300'
        Image {
          anchors.centerIn: parent
          source: '../images/refresh.png'
        }
        MaterialInk {
          anchors.fill: parent
          onClicked: reset()
        }
      }
      Rectangle {
        width: 34
        height: 28
        color: '#DD223300'
        Image {
          anchors.centerIn: parent
          source: '../images/check.png'
        }
        MaterialInk {
          anchors.fill: parent
          onClicked: Global.plannerWindowOpen = false
        }
      }
    }
  }
}
