import QtQuick 2.8
import '..'

Item {
  id: root

  signal dropUrl(url url)

  property bool downloadInProgress: false

  DropArea {
    id: dropArea
    anchors.fill: parent
    keys: ['text/uri-list']

    onDropped: {
      if (drop.hasUrls) {
        root.dropUrl(drop.urls[0]);
        drop.acceptProposedAction();
      }
    }
  }

  Rectangle {
    opacity: downloadInProgress || dropArea.containsDrag ? 1 : 0
    anchors.fill: parent
    color: Qt.rgba(0, 0, 0, 0.5)

    Behavior on opacity { StandardAnimation { duration: 200 } }
  }

  Rectangle {
    visible: dropArea.containsDrag
    anchors.centerIn: parent
    width: dropArea.containsDrag ? 200 : 0
    height: width
    radius: 36
    color: '#03A9F4'
    clip: true

    Behavior on width { StandardAnimation { duration: 200 } }

    SvgImage {
      anchors.centerIn: parent
      width: 200
      height: 200
      source: 'qrc:/images/planner/drop-area-border.svg'
    }

    Grid {
      anchors.centerIn: parent
      columns: 1
      horizontalItemAlignment: Grid.AlignHCenter

      SvgImage {
        width: 64
        height: 64
        source: 'qrc:/images/planner/map.svg'
      }

      Item {
        width: 1
        height: dropArea.containsDrag ? 10 : 50
        Behavior on height { StandardAnimation { duration: 200 } }
      }

      Text {
        color: Global.primaryTextColor
        text: 'Drop to Import'
        font.pixelSize: 16
      }
    }
  }
}
