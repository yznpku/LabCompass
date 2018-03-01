import QtQuick 2.8
import com.labcompass 1.0
import '..'

InstructionItem {
  id: root

  property alias model: lootView.model

  iconSource: 'qrc:/images/instruction/loot.svg'

  Text {
    color: Global.primaryTextColor
    text: 'Loot:'
  }

  Repeater {
    id: lootView

    Grid {
      columns: 2
      spacing: 4
      verticalItemAlignment: Grid.AlignVCenter

      SvgImage {
        source: modelData in Global.contentIconMapping ? 'qrc:/images/lab-content/' + Global.contentIconMapping[modelData] + '.svg' : ''
        width: 16
        height: 16
      }

      Text {
        color: Global.primaryTextColor
        text: modelData in Global.nameMapping ? Global.nameMapping[modelData] : modelData
      }
    }
  }
}
