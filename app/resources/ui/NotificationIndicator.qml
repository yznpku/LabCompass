import QtQuick 2.8

Rectangle {
  property int size: 8
  property int margin: 4

  color: '#f44336'
  width: size
  height: size
  radius: size / 2
  anchors {
    top: parent.top
    right: parent.right
    topMargin: margin
    rightMargin: margin
  }
}
