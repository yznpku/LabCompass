import QtQuick 2.8
import 'point.js' as Point

MouseArea {
  id: root

  property color color: 'white'
  clip: true
  cursorShape: enabled ? Qt.PointingHandCursor : Qt.ArrowCursor
  property point focusPoint
  property bool pressed: false
  onPressed: {
    pressed = true;
    layer1FadeOut.stop();
    layer1FadeIn.start();
  }
  onReleased: release();
  onExited: release();

  Rectangle {
    id: layer1
    anchors.fill: parent
    color: root.color
    opacity: 0.0
  }
  Rectangle {
    id: layer2
    color: root.color
    x: focusPoint.x - radius
    y: focusPoint.y - radius
    width: radius * 2
    height: radius * 2
  }

  NumberAnimation {
    id: layer1FadeIn
    target: layer1
    property: 'opacity'
    to: 0.08
    duration: 300
  }
  NumberAnimation {
    id: layer1FadeOut
    target: layer1
    property: 'opacity'
    to: 0.0
    duration: 100
  }
  NumberAnimation {
    id: layer2Expand
    duration: 0.5 * (root.width + root.height - 100) + 300
    target: layer2
    property: 'radius'
    easing.type: Easing.OutQuad
  }
  SequentialAnimation {
    id: layer2FadeOut
    PauseAnimation { duration: 50 }
    NumberAnimation {
      target: layer2
      property: 'opacity'
      to: 0.0
      duration: 300
    }
  }



  function showRipple(center) {
    if (!center)
      center = Qt.point(root.width / 2, root.height / 2);
    root.focusPoint = center;
    layer2Expand.stop();
    layer2FadeOut.stop();
    layer2.opacity = 0.2;
    layer2.radius = 0;

    layer2Expand.to = Math.max(Point.distance(root.focusPoint, Qt.point(0, 0)),
                               Point.distance(root.focusPoint, Qt.point(0, root.height)),
                               Point.distance(root.focusPoint, Qt.point(root.width, 0)),
                               Point.distance(root.focusPoint, Qt.point(root.width, root.height)));
    layer2Expand.start();
    layer2FadeOut.start();
  }

  function release() {
    if (pressed) {
      pressed = false;
      layer1FadeIn.stop();
      layer1FadeOut.start();
      showRipple(Qt.point(root.mouseX, root.mouseY));
    }
  }
}
