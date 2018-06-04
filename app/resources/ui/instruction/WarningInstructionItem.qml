import QtQuick 2.8
import com.labcompass 1.0

InstructionItem {
  id: root

  property string text

  color: '#D32F2F'
  iconSource: 'qrc:/images/instruction/warning.svg'

  Text {
    width: parent.width
    wrapMode: Text.WordWrap
    text: root.text
    color: Global.primaryTextColor
  }
}
