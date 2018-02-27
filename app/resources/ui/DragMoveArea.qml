import QtQuick 2.8

MouseArea {
  id: root

  signal drag(int dx, int dy)

  property bool dragging: false
  property point clickPos

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
