import QtQuick 2.8
import QtGraphicalEffects 1.0
import QtQuick.Controls 2.2
import QtQuick.Controls.Material 2.2
import com.labcompass 1.0

WindowWithShadow {
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
  property int planSilverCaches: 0
  property real planExpectedTreasureKeys: 3
  property real planExpectedEnchantments: 1

  signal back
  signal reset
  signal move(int moveTo)
  signal switchToDifficulty(string difficulty)
  signal updateLabNotes(string difficulty)

  onLinkModelChanged: linkView.requestPaint()

  Rectangle {
    id: root
    width: grid.width
    height: 429
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
          width: 120
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
          spacing: 160
          verticalItemAlignment: Grid.AlignVCenter

          Text {
            text: 'Labyrinth Planner'
            color: Global.primaryTextColor
            font.pixelSize: 32
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
                  width: 120
                  height: 30
                  z: 1
                  Text {
                    color: Global.primaryTextColor
                    text: modelData
                    anchors.centerIn: parent
                  }
                  MaterialInk {
                    anchors.fill: parent
                    enabled: !Global.labNoteUpdaterRunning && !Global.inLab
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
                  text: labNoteTitle ? 'Layout: ' + labNoteTitle : 'No lab notes loaded'
                  color: Global.primaryTextColor
                }
              }
              MaterialInk {
                id: updateButton
                width: 32
                height: 32
                anchors.right: parent.right
                anchors.rightMargin: 40
                anchors.verticalCenter: parent.verticalCenter
                onClicked: updateLabNotes(labDifficulty)
                enabled: !Global.labNoteUpdaterRunning && !Global.inLab
                Image {
                  id: updateButtonImage
                  source: '../images/update.png'
                  anchors.fill: parent
                  visible: parent.enabled
                }
                BusyIndicator {
                  anchors.fill: parent
                  running: !parent.enabled && !Global.inLab
                  Material.accent: Global.primaryTextColor
                }
              }
            }
          }
        }

        MaterialInk {
          id: closeButton
          width: 40
          height: 40
          anchors.right: parent.right
          anchors.rightMargin: 20
          anchors.top: parent.top
          anchors.topMargin: 10
          onClicked: Global.plannerWindowOpen = false;
          Image {
            anchors.centerIn: parent
            source: '../images/close.png'
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

        Grid {
          columns: 1
          spacing: 10
          z: 1

          Rectangle {
            id: labMap
            width: 830
            height: 260
            color: Global.primaryColor

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
                  color: modelData.name === 'Aspirant\'s Trial' ? '#101010' : '#E0E0E0'
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
                    font.pixelSize: 13
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
                id: mapMarker
                property int markerPos: Global.inLab ? Global.currentRoom : plan && plan.length > 0 ? plan[plan.length - 1] : 0
                x: (markerPos == 0 ? -20 : roomModel[markerPos].x) - 18
                y: (markerPos == 0 ? 129 : roomModel[markerPos].y) - 44
                source: '../images/map-marker.png'
                visible: false

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
              DropShadow {
                anchors.fill: mapMarker
                source: mapMarker
                verticalOffset: 2
                radius: 4.0
                samples: 8
                color: '#80000000'
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

          Item {
            width: 830
            height: 28
            Row {
              width: 710
              spacing: 4
              clip: true
              anchors.verticalCenter: parent.verticalCenter
              Text {
                anchors.verticalCenter: parent.verticalCenter
                text: plan.length  ? 'Plan: ' :
                      Global.inLab ? 'You cannot create or modify plans while inside the labyrinth.' :
                                     'To make a plan, click rooms in the order you\'ll travel through them.'
                color: !plan.length && Global.inLab ? '#e57373' : Global.primaryTextColor
                font.pixelSize: plan.length ? 20 : 16
              }
              Repeater {
                id: planView
                model: plan
                Rectangle {
                  width: 28
                  height: 28
                  color: Global.inLab && index + 1 == Global.currentPlanIndex ? Global.lightPrimaryColor : Global.primaryColor
                  Text {
                    anchors.centerIn: parent
                    text: modelData
                    color: Global.primaryTextColor
                    font.pixelSize: 16
                  }
                }
              }
            }
            Row {
              anchors.right: parent.right
              spacing: 10
              visible: !Global.inLab && plan.length
              Rectangle {
                width: 40
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
                width: 40
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

        Rectangle {
          width: 280
          height: 298
          color: Global.primaryColor
          Grid {
            anchors.horizontalCenter: parent.horizontalCenter
            horizontalItemAlignment: Grid.AlignHCenter
            padding: 10
            spacing: 16
            columns: 1
            Text {
              text: 'Plan Summary'
              font.pixelSize: 26
              color: Global.primaryTextColor
            }
            Grid {
              rowSpacing: 12
              columnSpacing: 30
              columns: 2
              verticalItemAlignment: Grid.AlignVCenter
              Text { color: Global.primaryTextColor; text: 'Rooms' }
              Text { color: Global.primaryTextColor; width: 30; horizontalAlignment: Text.AlignHCenter; text: planRooms }
              Text { color: Global.primaryTextColor; text: 'Length' }
              Text { color: Global.primaryTextColor; width: 30; horizontalAlignment: Text.AlignHCenter; text: planLength }
              Row {
                spacing: 4
                Image { source: '../images/lab-content/argus.png' }
                Text { color: Global.primaryTextColor; text: 'Argus' }
              }
              Text { color: Global.primaryTextColor; width: 30; horizontalAlignment: Text.AlignHCenter; text: planArgus }
              Row {
                spacing: 4
                Image { source: '../images/lab-content/gauntlet-puzzle.png' }
                Text { color: Global.primaryTextColor; text: 'Gauntlet/Puzzle' }
              }
              Text { color: 'white'; width: 30; horizontalAlignment: Text.AlignHCenter; text: planGPs }
              Row {
                spacing: 4
                Image { source: '../images/lab-content/darkshrine.png' }
                Text { color: Global.primaryTextColor; text: 'Darkshrine' }
              }
              Text { color: 'white'; width: 30; horizontalAlignment: Text.AlignHCenter; text: planDarkshrines }
              Row {
                spacing: 4
                Image { source: '../images/lab-content/silver-door.png' }
                Text { color: Global.primaryTextColor; text: 'Silver Cache' }
              }
              Text { color: Global.primaryTextColor; width: 30; horizontalAlignment: Text.AlignHCenter; text: planSilverCaches }
              Text { color: Global.primaryTextColor; text: 'Expected Treasure Keys' }
              Text { color: Global.primaryTextColor; width: 30; horizontalAlignment: Text.AlignHCenter; text: parent.round(planExpectedTreasureKeys, 2) }
              Text { color: Global.primaryTextColor; text: 'Expected Enchantments' }
              Text { color: Global.primaryTextColor; width: 30; horizontalAlignment: Text.AlignHCenter; text: parent.round(planExpectedEnchantments, 2) }

              function round(value, decimals) { return Number(Math.round(value+'e'+decimals)+'e-'+decimals); }
            }
          }
        }
      }
    }
  }
}


