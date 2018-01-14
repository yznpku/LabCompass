import QtQuick 2.8
import '..'

HighlightTab {
  id: root

  width: 48
  height: 24
  items: 2
  currentItem: 0

  activeLayerComponent: Row {
    Item {
      width: 24
      height: 24
      SvgImage {
        anchors.centerIn: parent
        source: 'qrc:/images/star-gold.svg'
      }
    }
    Item {
      width: 24
      height: 24
      SvgImage {
        anchors.centerIn: parent
        source: 'qrc:/images/map-marker-orange.svg'
      }
    }
  }

  inactiveLayerComponent: Row {
    Item {
      width: 24
      height: 24
      SvgImage {
        anchors.centerIn: parent
        source: 'qrc:/images/star-light.svg'
      }
    }
    Item {
      width: 24
      height: 24
      SvgImage {
        anchors.centerIn: parent
        source: 'qrc:/images/map-marker-light.svg'
      }
    }
  }
}
