import QtQuick 2.8
import com.labcompass 1.0
import '..'

Rectangle {
  id: root

  width: 24
  height: 24
//  color: Global.compassToolbarVisible ? Global.lightPrimaryColor : Global.backgroundColor
  color: Global.backgroundColor

  SvgImage {
    source: 'qrc:/images/view-list-light.svg'
    width: 18
    height: 18
    anchors.centerIn: parent
  }
}
