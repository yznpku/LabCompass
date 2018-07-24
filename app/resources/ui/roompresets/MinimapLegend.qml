import QtQuick 2.8
import com.labcompass 1.0
import '..'

Item {
  id: root
  width: grid.width
  height: grid.height

  Rectangle {
    anchors.fill: parent
    color: Global.primaryColor
  }

  Grid {
    id: grid
    anchors.centerIn: parent
    columns: 1
    spacing: 16
    leftPadding: 20
    rightPadding: 20
    topPadding: 12
    bottomPadding: 12
    horizontalItemAlignment: Grid.AlignHCenter

    Text {
      font.pixelSize: 20
      color: Global.primaryTextColor
      text: 'Legend'
    }

    Grid {
      columns: 2
      horizontalItemAlignment: Grid.AlignHCenter
      verticalItemAlignment: Grid.AlignVCenter
      rowSpacing: 12
      columnSpacing: 20

      Row {
        spacing: 2
        SvgImage { width: 26; height: 20; source: 'qrc:/images/compass/tile-full.svg' }
        SvgImage { width: 26; height: 20; source: 'qrc:/images/compass/tile-cross.svg' }
      }
      Text { color: Global.primaryTextColor; text: 'Path' }

      SvgImage { width: 26; height: 20; source: 'qrc:/images/compass/tile-trap.svg' }
      Text { color: Global.primaryTextColor; text: 'Traps' }

      SvgImage { width: 26; height: 20; source: 'qrc:/images/compass/door-target.svg' }
      Text { color: Global.primaryTextColor; text: 'Exit' }

      SvgImage { width: 26; height: 20; source: 'qrc:/images/compass/loot-normal.svg' }
      Text { color: Global.primaryTextColor; text: 'Loot' }
    }
  }
}


