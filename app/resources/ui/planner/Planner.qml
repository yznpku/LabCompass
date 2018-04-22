import QtQuick 2.8
import QtGraphicalEffects 1.0
import QtQuick.Controls 2.2
import QtQuick.Controls.Material 2.2
import com.labcompass 1.0
import '..'

WindowWithShadow {
  id: window
  property var labyrinthModel: Global.model.labyrinthModel

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
      height: 2
      color: Qt.lighter(Global.primaryColor)
    }

    Grid {
      columns: 2
      columnSpacing: 20
      rowSpacing: 10

      leftPadding: 40
      rightPadding: 40

      LabyrinthMapDisplay {
        id: labyrinthMapDisplay
        objectName: 'labyrinthMapDisplay'
        width: 830
        height: 260
        roomModel: Global.model.roomModel
        connectionModel: Global.model.connectionModel
        goldenDoorModel: Global.model.goldenDoorModel
      }

      PlanSummaryDisplay {
        id: planSummaryDisplay
        width: 280
        height: 260
        color: Global.primaryColor
        model: Global.model.planSummaryModel
      }

      PlannedRouteDisplay {
        id: plannedRouteDisplay
        width: 830
        height: 28
        plannedRouteModel: Global.model.plannedRouteModel
      }

      Item {
        width: 280
        height: 28

        Row {
          spacing: 4
          anchors.verticalCenter: parent.verticalCenter
          anchors.right: parent.right

          Text {
            text: 'Donate: '
            color: Global.primaryTextColor
            font.pixelSize: 20
          }
          MaterialInk {
            width: 24
            height: 24
            onClicked: openUrl('https://www.paypal.me/futurecode')
            SvgImage {
              source: 'qrc:/images/paypal.svg'
              anchors.fill: parent
            }
          }
          MaterialInk {
            width: 24
            height: 24
            onClicked: openUrl('https://www.patreon.com/futurecode')
            SvgImage {
              source: 'qrc:/images/patreon.svg'
              anchors.fill: parent
            }
          }
        }
      }
    }
  }
}
