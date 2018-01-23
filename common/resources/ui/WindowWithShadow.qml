import QtQuick 2.8
import QtGraphicalEffects 1.0
import com.labcompass 1.0

Item {
  id: root
  width: contents.width + 20
  height: contents.height + 20

  default property alias content: contents.children
  property var root: contents

  RectangularGlow {
    x: 10
    y: 13
    width: contents.width
    height: contents.height
    glowRadius: 3
    spread: 0.0
    color: Qt.rgba(0, 0, 0, 0.8)
    cornerRadius: glowRadius
  }

  Item {
    id: contents
    x: 10
    y: 10
    width: childrenRect.x + childrenRect.width
    height: childrenRect.y + childrenRect.height

    Rectangle {
      anchors.fill: parent
      color: Global.backgroundColor
    }
  }
}
