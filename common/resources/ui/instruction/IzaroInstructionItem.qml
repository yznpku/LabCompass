import QtQuick 2.8
import com.labcompass 1.0
import '..'

InstructionItem {
  id: root

  property string mechanics

  iconSource: mechanics === 'ChargeDisruptors' || mechanics === 'Idols' ? 'qrc:/images/instruction/izaro-wait.svg'
                                                                        : 'qrc:/images/instruction/izaro-kill.svg'

  Text {
    text: 'Defeat Izaro'
    color: Global.primaryTextColor
  }
  Row {
    visible: mechanics
    spacing: 4
    SvgImage {
      source: 'qrc:/images/instruction/mechanics.svg'
    }
    Text {
      text: mechanics in Global.nameMapping ? Global.nameMapping[mechanics] : mechanics
      color: Global.primaryTextColor
    }
  }
}
