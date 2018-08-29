import QtQuick 2.8
import '..'

Item {
  id: root

  property color color
  property url iconSource
  property alias iconComponent: iconComponentLoader.sourceComponent
  default property alias content: column.children

  width: 260
  height: background.height + 8

  Rectangle {
    id: background
    color: root.color
    width: root.width
    height: Math.max(40, column.height + 12)
    opacity: 0.75
  }
  SvgImage {
    id: icon
    source: root.iconSource
    anchors.verticalCenter: background.verticalCenter
    x: (40 - width) / 2
    width: 20
    height: 20
  }
  Column {
    id: column
    x: 40
    anchors.verticalCenter: background.verticalCenter
    width: root.width - 40
    spacing: 4
  }

  Loader {
    id: iconComponentLoader
    anchors.centerIn: icon
  }
}
