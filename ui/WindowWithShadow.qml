import QtQuick 2.8
import QtGraphicalEffects 1.0

Item {
  id: root
  width: root.children[1].width + 20
  height: root.children[1].height + 20

  RectangularGlow {
    x: 10
    y: 13
    width: root.children[1].width
    height: root.children[1].height
    glowRadius: 3
    spread: 0.0
    color: Qt.rgba(0, 0, 0, 0.8)
    cornerRadius: glowRadius
  }

  onChildrenChanged: {
    children[1].x = children[1].y = 10;
  }
}
