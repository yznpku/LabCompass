import QtQuick 2.8
import com.labcompass 1.0

Item {
  id: root
  property alias text: text.text
  property bool active: true

  Text {
    id: text
    anchors.centerIn: parent
    font.pixelSize: 16
    color: root.active ? Global.primaryTextColor : Global.secondaryTextColor
  }
}
