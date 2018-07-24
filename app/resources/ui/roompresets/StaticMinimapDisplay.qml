import QtQuick 2.8
import com.labcompass 1.0
import '../point.js' as Point
import '..'

Item {
  id: root
  property var presetModel

  SvgImage {
    anchors.fill: parent
    source: presetModel && presetModel.areaCode ? 'qrc:/images/room-preset/' + presetModel.areaCode + '.svg' : ''
  }

  Repeater {
    id: exitDirectionView
    model: presetModel ? presetModel.doorExitLocations : []

    SvgImage {
      x: modelData.tileRect.x * root.width
      y: modelData.tileRect.y * root.height
      width: modelData.tileRect.width * root.width
      height: modelData.tileRect.height * root.height
      source: 'qrc:/images/compass/door-target.svg'
    }
  }

  Repeater {
    id: contentLocationsView
    model: presetModel ? presetModel.contentLocations: []

    SvgImage {
      x: modelData.tileRect.x * root.width
      y: modelData.tileRect.y * root.height
      width: modelData.tileRect.width * root.width
      height: modelData.tileRect.height * root.height
      source: 'qrc:/images/compass/loot-normal.svg'
    }
  }
}
