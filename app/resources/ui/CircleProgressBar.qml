import QtQuick 2.8
import QtQuick.Controls 2.2
import QtGraphicalEffects 1.0

ProgressBar {
  id: root

  property real circleWidth: 4
  property color color: 'black'

  background: null

  contentItem: Item {

    Rectangle {
      id: ring
      anchors.fill: parent
      anchors.margins: border.width / 2
      radius: Math.max(width, height) / 2
      color: 'transparent'
      border.width: root.circleWidth
      visible: false
    }

    ConicalGradient {
      source: ring
      anchors.fill: parent
      gradient: Gradient {
        GradientStop { position: 0; color: root.color }
        GradientStop { position: root.value; color: root.color }
        GradientStop { position: root.value + 0.001; color: 'transparent' }
        GradientStop { position: 1; color: 'transparent' }
      }
    }
  }
}
