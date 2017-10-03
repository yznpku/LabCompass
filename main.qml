import QtQuick 2.8

Rectangle {
  color: Qt.rgba(1, 1, 1, 0.5)
  x: 100
  y: 100
  width: 640
  height: 480

  Rectangle {
    color: 'white'
    width: 50
    height: 50
    anchors.centerIn: parent

    MouseArea {
      anchors.fill: parent
      onClicked: console.log('click')
    }
  }
}
