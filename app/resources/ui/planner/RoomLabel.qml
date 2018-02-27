import QtQuick 2.8
import com.labcompass 1.0
import '..'

Rectangle {
  property string roomName
  property var roomContents: []

  x: -width / 2 + parent.width / 2
  y: -height - 36 + parent.height / 2
  width: grid.width
  height: grid.height
  color: Qt.rgba(0, 0, 0, 0.8)
  Grid {
    id: grid
    padding: 10
    spacing: 16
    columns: 1
    horizontalItemAlignment: Grid.AlignHCenter
    Text {
      color: Global.primaryTextColor
      text: roomName
    }
    Grid {
      spacing: 2
      columns: 1
      horizontalItemAlignment: Grid.AlignHCenter
      Repeater {
        model: roomContents
        Row {
          spacing: 2
          SvgImage {
            source: modelData in Global.contentIconMapping ? 'qrc:/images/lab-content/' + Global.contentIconMapping[modelData] + '.svg' : ''
          }
          Text {
            text: modelData in Global.nameMapping ? Global.nameMapping[modelData] : modelData
            color: Global.primaryTextColor
            font.pixelSize: 14
          }
        }
      }
    }
  }
  Rectangle {
    x: 10
    y: 36
    width: grid.width - 20
    height: 1
    color: Qt.lighter(Global.primaryColor)
    visible: roomContents.length
  }
}
