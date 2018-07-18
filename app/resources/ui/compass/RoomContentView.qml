import QtQuick 2.8
import com.labcompass 1.0
import '..'

Row {
  id: root
  property var model

  spacing: 2

  Repeater {
    id: contentView
    model: root.model

    SvgImage {
      source: modelData in Global.contentIconMapping ? 'qrc:/images/lab-content/' + Global.contentIconMapping[modelData] + '.svg' : ''
    }
  }
}
