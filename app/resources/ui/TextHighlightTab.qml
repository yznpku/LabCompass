import QtQuick 2.8

HighlightTab {
  id: root

  property var model: []

  items: model.length ? model.length : 1
  onItemClicked: currentItem = index

  activeLayerComponent: Row {
    Repeater {
      model: root.model
      TabLabel {
        width: root.width / root.items
        height: root.height
        active: true
        text: modelData
      }
    }
  }

  inactiveLayerComponent: Row {
    Repeater {
      model: root.model
      TabLabel {
        width: root.width / root.items
        height: root.height
        active: false
        text: modelData
      }
    }
  }
}
