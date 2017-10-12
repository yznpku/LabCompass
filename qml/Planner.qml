import QtQuick 2.8
import QtGraphicalEffects 1.0
import QtQuick.Controls 2.2
import QtQuick.Controls.Material 2.2
import com.labcompass 1.0

Rectangle {
  id: root
  property string labDifficulty: 'Uber'
  property string labNoteTitle: ''
  property bool updatingLabNotes: false
  property var roomModel: []
  property var linkModel: []
  property var goldenDoorModel: []
  property var plan: []
  property int planRooms: 0
  property int planLength: 0
  property int planGPs: 0
  property int planArgus: 0
  property int planDarkshrines: 0
  property int planExpectedTreasureKeys: 3
  property int planExpectedEnchantments: 1

  signal back
  signal reset
  signal move(int moveTo)
  signal switchToDifficulty(string difficulty)
  signal updateLabNotes(string difficulty)

  onLinkModelChanged: linkView.requestPaint()

  width: grid.width
  height: grid.height
  color: Global.backgroundColor

  Grid {
    id: grid
    columns: 1
    spacing: 20
    topPadding: 10
    bottomPadding: 20

    Item {
      height: 60
      width: root.width

      Item { RotationAnimation on rotation { loops: Animation.Infinite; from: 0; to: 360 }}

      Rectangle {
        id: activeLabDifficultyHighlight
        property var activeViewItem
        parent: labDifficultyView
        width: 90
        height: 30
        x: activeViewItem ? parent.mapFromItem(activeViewItem, 0, 0).x : 0
        color: Global.primaryColor
        Component.onCompleted: activeViewItem = Qt.binding(function() { return labDifficultyView.itemAt(labDifficultyView.model.indexOf(labDifficulty)) })
        Behavior on x {
          NumberAnimation {
            easing.type: Easing.Bezier
            easing.bezierCurve: [0.4, 0.0, 0.2, 1.0, 1.0, 1.0]
            duration: 150
          }
        }
        Rectangle {
          color: Global.lightPrimaryColor
          height: 2
          anchors {
            left: parent.left
            right: parent.right
            top: parent.bottom
          }
        }
      }

      Grid {
        columns: 2
        leftPadding: 40
        spacing: 40
        verticalItemAlignment: Grid.AlignVCenter

        Text {
          text: 'Labyrinth Planner'
          color: Global.primaryTextColor
          font.pointSize: 24
        }

        Grid {
          columns: 1
          spacing: 10
          Grid {
            columns: 4
            spacing: 2
            Repeater {
              id: labDifficultyView
              model: ['Normal', 'Cruel', 'Merciless', 'Uber']
              Item {
                width: 90
                height: 30
                z: 1
                Text {
                  color: Global.primaryTextColor
                  text: modelData
                  anchors.centerIn: parent
                }
                MaterialInk {
                  anchors.fill: parent
                  onClicked: {
                    labDifficulty = modelData;
                    switchToDifficulty(labDifficulty);
                  }
                }
              }
            }
          }
          Item {
            width: labDifficultyView.parent.width
            height: 30
            Item {
              anchors {
                left: parent.left
                top: parent.top
                right: updateButton.left
                bottom: parent.bottom
              }
              Text {
                anchors.centerIn: parent
                text: labNoteTitle ? labNoteTitle : 'No lab notes loaded'
                color: Global.primaryTextColor
              }
            }
            MaterialInk {
              id: updateButton
              width: 32
              height: 32
              anchors.right: parent.right
              anchors.verticalCenter: parent.verticalCenter
              onClicked: updateLabNotes(labDifficulty)
              enabled: !Global.labNoteUpdaterRunning
              Image {
                id: updateButtonImage
                source: '../images/update.png'
                anchors.fill: parent
                visible: parent.enabled
              }
              BusyIndicator {
                anchors.fill: parent
                running: !parent.enabled
                Material.accent: Global.primaryTextColor
              }
            }
          }
        }
      }
    }

    Rectangle {
      width: root.width
      height: 1
      color: Qt.lighter(Global.primaryColor)
    }

    Grid {
      columns: 2
      spacing: 20

      leftPadding: 40
      rightPadding: 40

      Rectangle {
        id: labMap
        width: 830
        height: 260
        color: Global.primaryColor
        z: 1

        Canvas {
          id: linkView
          anchors.fill: parent
          onPaint: {
            var ctx = linkView.getContext('2d');
            ctx.clearRect(0, 0, width, height);

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
          model: roomModel

          Item {
            x: modelData.x - 24
            y: modelData.y - 24
            width: 48
            height: 48
            visible: !modelData.invalid

            MouseArea {
              anchors.fill: parent
              onClicked: if (!Global.inLab) move(index);
            }

            RectangularGlow {
              opacity: plan.indexOf(index) >= 0 ? 1 : 0
              anchors.fill: rect
              glowRadius: 4
              spread: 0.6
              color: "white"
              cornerRadius: 24

              Behavior on opacity {
                NumberAnimation {
                  easing.type: Easing.Bezier
                  easing.bezierCurve: [0.4, 0.0, 0.2, 1.0, 1.0, 1.0]
                  duration: 150
                }
              }
            }

            Rectangle {
              id: rect
              anchors.fill: parent
              visible: false
              radius: 24
              color: modelData.name === 'Aspirant\'s Trial' ? '#101010' : '#A1887F'
              Image {
                anchors.centerIn: parent
                source: modelData.name === 'Aspirant\'s Trial' ? '../images/lab-content/izaro.png' : ''
                scale: 0.75
              }
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
                  source: modelData in Global.contentIconMapping ? '../images/lab-content/' + Global.contentIconMapping[modelData] + '.png' : ''
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

        Repeater {
          id: goldenDoorView
          model: goldenDoorModel

          Item {
            x: (roomModel[modelData[0]].x + roomModel[modelData[1]].x) / 2
            y: (roomModel[modelData[0]].y + roomModel[modelData[1]].y) / 2

            Image {
              id: goldenDoorIcon
              anchors.centerIn: parent
              source: '../images/lab-content/golden-door.png'
              visible: false
            }
            DropShadow {
              anchors.fill: goldenDoorIcon
              source: goldenDoorIcon
              verticalOffset: 2
              radius: 4.0
              samples: 8
              color: '#80000000'
            }
          }
        }

        Item {
          anchors.fill: parent
          clip: true
          Image {
            property int markerPos: plan && plan.length > 0 ? plan[plan.length - 1] : 0
            x: (markerPos == 0 ? -20 : roomModel[markerPos].x) - 18
            y: (markerPos == 0 ? 129 : roomModel[markerPos].y) - 32
            source: '../images/map-marker.png'

            Behavior on x {
              NumberAnimation {
                easing.type: Easing.Bezier
                easing.bezierCurve: [0.4, 0.0, 0.2, 1.0, 1.0, 1.0]
                duration: 150
              }
            }
            Behavior on y {
              NumberAnimation {
                easing.type: Easing.Bezier
                easing.bezierCurve: [0.4, 0.0, 0.2, 1.0, 1.0, 1.0]
                duration: 150
              }
            }
          }
        }

        Repeater {
          id: roomTooltipView
          model: roomModel

          Item {
            x: modelData.x - 24
            y: modelData.y - 24
            width: 48
            height: 48
            visible: !modelData.invalid

            TooltipHoverArea {
              id: roomHoverArea
              anchors.fill: parent
              cursorShape: Qt.PointingHandCursor
            }

            RoomLabel {
              roomName: modelData['name']
              roomContents: getRoomContents(modelData)
              opacity: roomHoverArea.shouldDisplayTooltip ? 1 : 0

              function getRoomContents(modelData) {
                var roomContents = [];
                if ('contents' in modelData)
                  for (var i = 0; i < modelData['contents'].length; i++)
                    roomContents.push(modelData['contents'][i]);
                if ('weapon' in modelData)
                  roomContents.push(modelData['weapon']);
                if ('mechanics' in modelData)
                  for (var i = 0; i < modelData['mechanics'].length; i++)
                    roomContents.push(modelData['mechanics'][i]);
                if ('secret_passage' in modelData) {
                  var name = modelData['secret_passage'] in Global.nameMapping ? Global.nameMapping[modelData['secret_passage']] : modelData['secret_passage']
                  roomContents.push('Secret Passage (' + name + ')')
                }
                return roomContents;
              }

              Behavior on opacity {
                NumberAnimation {
                  easing.type: Easing.Bezier
                  easing.bezierCurve: [0.4, 0.0, 0.2, 1.0, 1.0, 1.0]
                  duration: 100
                }
              }
            }
          }
        }
      }

      Rectangle {
        width: 280
        height: 260
        color: Global.primaryColor
        Grid {
          anchors.horizontalCenter: parent.horizontalCenter
          horizontalItemAlignment: Grid.AlignHCenter
          padding: 10
          spacing: 20
          columns: 1
          Text {
            text: 'SUMMARY'
            font.pointSize: 16
            color: 'white'
          }
          Grid {
            rowSpacing: 12
            columnSpacing: 30
            columns: 2
            verticalItemAlignment: Grid.AlignVCenter
            Text { color: 'white'; text: 'Rooms' }
            Text { color: 'white'; text: planRooms; width: 25 }
            Text { color: 'white'; text: 'Length' }
            Text { color: 'white'; text: planLength }
            Row {
              spacing: 4
              Image { source: '../images/lab-content/argus.png' }
              Text { color: 'white'; text: 'Argus' }
            }
            Text { color: 'white'; text: planArgus }
            Row {
              spacing: 4
              Image { source: '../images/lab-content/gauntlet-puzzle.png' }
              Text { color: 'white'; text: 'Gauntlet/Puzzle' }
            }
            Text { color: 'white'; text: planGPs }
            Row {
              spacing: 4
              Image { source: '../images/lab-content/darkshrine.png' }
              Text { color: 'white'; text: 'Darkshrine' }
            }
            Text { color: 'white'; text: planDarkshrines }
            Text { color: 'white'; text: 'Expected Treasure Keys' }
            Text { color: 'white'; text: planExpectedTreasureKeys }
            Text { color: 'white'; text: 'Expected Enchantments' }
            Text { color: 'white'; text: planExpectedEnchantments }
          }
        }
      }

      Row {
        spacing: 4
        Item {
          width: 80
          height: 28
          Text {
            anchors.centerIn: parent
            text: 'Plan:'
            color: Global.primaryTextColor
            font.pointSize: 16
          }
        }
        Repeater {
          id: planView
          model: plan
          Rectangle {
            width: 28
            height: 28
            color: Global.primaryColor
            Text {
              anchors.centerIn: parent
              text: modelData
              color: Global.primaryTextColor
              font.pointSize: 12
            }
          }
        }
      }

      Row {
        spacing: 10
        visible: !Global.inLab
        Rectangle {
          width: 55
          height: 28
          color: Global.primaryColor
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
          width: 55
          height: 28
          color: Global.primaryColor
          Image {
            anchors.centerIn: parent
            source: '../images/refresh.png'
          }
          MaterialInk {
            anchors.fill: parent
            onClicked: reset()
          }
        }
      }
    }
  }
}
