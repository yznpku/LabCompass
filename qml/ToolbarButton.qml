import QtQuick 2.8

Rectangle {
  id: root
  property string source
  property bool active
  signal clicked()

  height: 24
  width: 24
  color: active ? '#DDFFFFFF' : '#DDCCFF00'
  Image {
    source: root.source
    anchors.centerIn: parent
    width: 16
    height: 16
    opacity: 0.8
  }
  MaterialInk {
    anchors.fill: parent
    onClicked: root.clicked()
  }
}
