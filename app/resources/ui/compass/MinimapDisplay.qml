import QtQuick 2.8
import com.labcompass 1.0
import '../point.js' as Point
import '..'

Item {
  id: root
  property var instructionModel

  SvgImage {
    anchors.fill: parent
    source: 'qrc:/images/room-preset/tile/' + instructionModel.preset.keyword + '.svg'
  }

  Repeater {
    id: exitDirectionView
    model: instructionModel.roomDoorExitDirections

    SvgImage {
      property var tileRect: getTileRect(instructionModel.preset.minimap.directions[modelData])
      x: tileRect.x
      y: tileRect.y
      width: tileRect.width
      height: tileRect.height
      source: modelData === instructionModel.nextRoomDirection ? 'qrc:/images/compass/door-target.svg'
                                                               : 'qrc:/images/compass/door-normal.svg'
    }
  }

  Repeater {
    id: contentLocationsView
    model: instructionModel.contentLocations

    SvgImage {
      property var tileRect: getTileRect(instructionModel.preset.minimap.directions[modelData.direction])
      x: tileRect.x
      y: tileRect.y
      width: tileRect.width
      height: tileRect.height
      source: instructionModel.nextRoomConnectionType === 'secret' && !modelData.major ? 'qrc:/images/compass/loot-active.svg'
                                                                                       : 'qrc:/images/compass/loot-normal.svg'
    }
  }

  RoomContentView {
    anchors.bottom: parent.bottom
    model: instructionModel.roomLoot
  }

  function getTileRect(coord) {
    var row = coord[0];
    var column = coord[1];
    var rows = instructionModel.preset.minimap.rows;
    var columns = instructionModel.preset.minimap.columns;
    var pageCenter = Qt.point(root.width / 2, root.height / 2);
    var rowd = row - (rows - 1) / 2;
    var columnd = column - (columns - 1) / 2;
    var scale = 10 / Math.max(rows, columns, 7);
    var tileWidth = root.width / 10;
    var tileHeight = root.height / 10;
    var d = Point.scale(Qt.point(tileWidth * (columnd - rowd), tileHeight * (columnd + rowd)), 0.5 * scale);
    var tileCenter = Point.add(pageCenter, d);
    return Qt.rect(tileCenter.x - tileWidth / 2 * scale, tileCenter.y - tileHeight / 2 * scale, tileWidth * scale, tileHeight * scale)
  }
}
