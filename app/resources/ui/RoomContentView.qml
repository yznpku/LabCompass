import QtQuick 2.8
import com.labcompass 1.0

Row {
  id: root
  property var model

  spacing: 2

  Repeater {
    id: contentView
    model: root.model

    RoomContentIcon {
      content: modelData
    }
  }
}
