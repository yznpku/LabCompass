import QtQuick 2.8
import QtGraphicalEffects 1.0
import com.labcompass 1.0

Item {
  id: root

  property string content

  width: 16
  height: 16

  SvgImage {
    id: icon
    anchors.fill: parent
    source: content in Global.contentIconMapping ? 'qrc:/images/lab-content/' + Global.contentIconMapping[content] + '.svg' : ''
  }

  DropShadow {
    anchors.fill: parent
    source: icon
    verticalOffset: 1
    radius: 2.0
    samples: 8
    color: '#80000000'
  }
}
