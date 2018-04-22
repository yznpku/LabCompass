import QtQuick 2.8
import '..'

Rectangle {
  id: root
  property var model

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
      Text { color: Global.primaryTextColor; width: 30; horizontalAlignment: Text.AlignHCenter; text: model.rooms }
      Text { color: Global.primaryTextColor; text: 'Length' }
      Text { color: Global.primaryTextColor; width: 30; horizontalAlignment: Text.AlignHCenter; text: model.length }
      Row {
        spacing: 4
        SvgImage { source: 'qrc:/images/lab-content/argus.svg' }
        Text { color: Global.primaryTextColor; text: 'Argus' }
      }
      Text { color: Global.primaryTextColor; width: 30; horizontalAlignment: Text.AlignHCenter; text: model.argus }
      Row {
        spacing: 4
        SvgImage { source: 'qrc:/images/lab-content/gauntlet-puzzle.svg' }
        Text { color: Global.primaryTextColor; text: 'Trove/Lockbox' }
      }
      Text { color: 'white'; width: 30; horizontalAlignment: Text.AlignHCenter; text: model.troves }
      Row {
        spacing: 4
        SvgImage { source: 'qrc:/images/lab-content/darkshrine.svg' }
        Text { color: Global.primaryTextColor; text: 'Darkshrine' }
      }
      Text { color: 'white'; width: 30; horizontalAlignment: Text.AlignHCenter; text: model.darkshrines }
      Row {
        spacing: 4
        SvgImage { source: 'qrc:/images/lab-content/silver-door.svg' }
        Text { color: Global.primaryTextColor; text: 'Silver Cache' }
      }
      Text { color: Global.primaryTextColor; width: 30; horizontalAlignment: Text.AlignHCenter; text: model.silverCaches }
    }
  }
}
