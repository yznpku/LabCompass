import QtQuick 2.8
import QtGraphicalEffects 1.0
import QtQuick.Controls 2.2
import QtQuick.Controls.Material 2.2
import com.labcompass 1.0
import '..'

WindowWithShadow {
  id: window
  property var labyrinthModel: Global.model.labyrinthModel
  property var planSummaryModel: Global.model.planSummaryModel

  signal drag(int dx, int dy)
  signal importLabNotesButtonClicked
  signal openUrl(string url)

  Column {
    id: grid
    spacing: 20
    topPadding: 20
    bottomPadding: 20
    width: 1210

    Item {
      height: 50
      width: grid.width

      Item { RotationAnimation on rotation { loops: Animation.Infinite; from: 0; to: 360 }}

      Grid {
        columns: 5
        leftPadding: 20
        spacing: 20
        anchors.verticalCenter: parent.verticalCenter
        verticalItemAlignment: Grid.AlignVCenter

        DragMoveArea {
          width: 350
          height: 80
          onDrag: window.drag(dx, dy)

          Text {
            text: 'Labyrinth Planner'
            anchors.centerIn: parent
            color: Global.primaryTextColor
            font.pixelSize: 32
          }
        }

        Item {
          width: 400
          height: 30
          Text {
            anchors.centerIn: parent
            text: labyrinthModel.title ? 'Layout: ' + labyrinthModel.title : 'No lab notes loaded'
            color: Global.primaryTextColor
          }
        }

        MaterialInk {
          width: 120
          height: 30
          onClicked: openUrl('http://www.poelab.com')
          Text {
            anchors.centerIn: parent
            text: 'Get Maps'
            color: Global.primaryTextColor
          }
          NotificationIndicator {
            visible: Global.model.labMapOutdated
          }
        }

        MaterialInk {
          width: 120
          height: 30
          onClicked: importLabNotesButtonClicked()
          Rectangle {
            anchors.fill: parent
            color: '#2196F3'
            radius: 2
            z: -1
            Text {
              anchors.centerIn: parent
              text: 'Import Maps'
              color: Global.primaryTextColor
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
        onClicked: Global.plannerWindowOpen = false;
        SvgImage {
          anchors.centerIn: parent
          source: 'qrc:/images/close.svg'
        }
      }
    }

    Rectangle {
      width: grid.width
      height: 1
      color: Qt.lighter(Global.primaryColor)
    }

    Grid {
      columns: 2
      spacing: 20

      leftPadding: 40
      rightPadding: 40

      Column {
        spacing: 10
        z: 1

        LabyrinthMapDisplay {
          id: labyrinthMapDisplay
          objectName: 'labyrinthMapDisplay'
          width: 830
          height: 260
          roomModel: Global.model.roomModel
          connectionModel: Global.model.connectionModel
          goldenDoorModel: Global.model.goldenDoorModel
        }

        PlannedRouteDisplay {
          id: plannedRouteDisplay
          width: 830
          height: 28
          plannedRouteModel: Global.model.plannedRouteModel
        }
      }

      Rectangle {
        id: planSummary
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
            Text { color: Global.primaryTextColor; width: 30; horizontalAlignment: Text.AlignHCenter; text: planSummaryModel.rooms }
            Text { color: Global.primaryTextColor; text: 'Length' }
            Text { color: Global.primaryTextColor; width: 30; horizontalAlignment: Text.AlignHCenter; text: planSummaryModel.length }
            Row {
              spacing: 4
              SvgImage { source: 'qrc:/images/lab-content/argus.svg' }
              Text { color: Global.primaryTextColor; text: 'Argus' }
            }
            Text { color: Global.primaryTextColor; width: 30; horizontalAlignment: Text.AlignHCenter; text: planSummaryModel.argus }
            Row {
              spacing: 4
              SvgImage { source: 'qrc:/images/lab-content/gauntlet-puzzle.svg' }
              Text { color: Global.primaryTextColor; text: 'Trove/Lockbox' }
            }
            Text { color: 'white'; width: 30; horizontalAlignment: Text.AlignHCenter; text: planSummaryModel.troves }
            Row {
              spacing: 4
              SvgImage { source: 'qrc:/images/lab-content/darkshrine.svg' }
              Text { color: Global.primaryTextColor; text: 'Darkshrine' }
            }
            Text { color: 'white'; width: 30; horizontalAlignment: Text.AlignHCenter; text: planSummaryModel.darkshrines }
            Row {
              spacing: 4
              SvgImage { source: 'qrc:/images/lab-content/silver-door.svg' }
              Text { color: Global.primaryTextColor; text: 'Silver Cache' }
            }
            Text { color: Global.primaryTextColor; width: 30; horizontalAlignment: Text.AlignHCenter; text: planSummaryModel.silverCaches }
          }
        }
      }
    }
  }
}
