import QtQuick 2.8
import com.labcompass 1.0

Row {
  id: root
  spacing: 4

  signal drag(int deltaX, int deltaY)
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
    MouseArea {
      property bool dragging: false
      property point clickPos
      anchors.fill: parent
      cursorShape: dragging ? Qt.ClosedHandCursor : Qt.OpenHandCursor
      onPressed: {
        dragging = true;
        clickPos = Qt.point(mouse.x, mouse.y);
      }
      onReleased: {
        dragging = false;
      }
      onPositionChanged: {
        root.drag(mouse.x - clickPos.x, mouse.y - clickPos.y);
      }
    }
  }

  ToolbarButton {
    source: '../images/close.png'
    onClicked: exit()
  }
}
