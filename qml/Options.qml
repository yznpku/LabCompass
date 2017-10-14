import QtQuick 2.8
import com.labcompass 1.0

WindowWithShadow {
  signal openUrl(string url)

  Rectangle {
    id: root
    width: 400
    height: 100
    color: Global.backgroundColor

    Row {
      x: 40
      y: 20
      height: 60
      spacing: 20
      Text {
        anchors.verticalCenter: parent.verticalCenter
        text: 'LabCompass'
        color: Global.primaryTextColor
        font.pointSize: 24
      }
      Column {
        anchors.verticalCenter: parent.verticalCenter
        Text {
          color: Global.primaryTextColor
          text: 'dev-version'
        }
        Row {
          MaterialInk {
            width: 32
            height: 32
            onClicked: openUrl('https://github.com/yznpku/LabCompass')
            Image {
              anchors.centerIn: parent
              source: '../images/github-circle.png'
            }
          }
        }
      }
    }

    MaterialInk {
      id: closeButton
      width: 40
      height: 40
      anchors.right: parent.right
      anchors.rightMargin: 10
      anchors.top: parent.top
      anchors.topMargin: 10
      onClicked: Global.optionsWindowOpen = false;
      Image {
        anchors.centerIn: parent
        source: '../images/close.png'
      }
    }
  }
}
