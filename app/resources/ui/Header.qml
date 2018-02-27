import QtQuick 2.8
import com.labcompass 1.0

Row {
  id: root
  spacing: 4

  signal drag(int dx, int dy)
  signal exit()

  Rectangle {
    height: 24
    width: 120
    color: Global.lightPrimaryColor
    Text {
      text: 'LabCompass'
      color: Global.primaryTextColor
      anchors.centerIn: parent
    }
    DragMoveArea {
      anchors.fill: parent
      onDrag: root.drag(dx, dy)
    }
  }

  ToolbarButton {
    source: 'qrc:/images/close.svg'
    onClicked: exit()
  }
}
