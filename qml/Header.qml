import QtQuick 2.8

Row {
  id: root
  spacing: 4

  signal drag(int deltaX, int deltaY)
  signal exit()

  Rectangle {
    height: 24
    width: 80
    color: '#DD223300'
    Text {
      text: 'LabCompass'
      color: '#CCFF00'
      anchors.centerIn: parent
    }
    MouseArea {
      property point clickPos
      anchors.fill: parent
      onPressed: {
        clickPos = Qt.point(mouse.x, mouse.y)
      }
      onPositionChanged: {
        root.drag(mouse.x - clickPos.x, mouse.y - clickPos.y)
      }
    }
  }

  ToolbarButton {
    source: '../images/close.png'
    onClicked: exit()
  }
}
