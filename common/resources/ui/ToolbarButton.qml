import QtQuick 2.8
import com.labcompass 1.0

Rectangle {
  id: root
  property string source
  property bool active
  signal clicked()

  height: 24
  width: 24
  color: active ? Global.lightPrimaryColor : Global.backgroundColor
  SvgImage {
    source: root.source
    anchors.centerIn: parent
  }
  MaterialInk {
    anchors.fill: parent
    onClicked: root.clicked()
  }
}
