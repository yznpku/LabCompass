import QtQuick 2.8
import com.labcompass 1.0
import '..'

InstructionItem {
  id: root

  property var model

  property string name: model ? model.title : ''
  property string difficulty: model ? model.difficulty : ''

  iconSource: {
    'Normal': 'qrc:/images/instruction/loaded-map-normal.svg',
    'Cruel': 'qrc:/images/instruction/loaded-map-cruel.svg',
    'Merciless': 'qrc:/images/instruction/loaded-map-merciless.svg',
    'Uber': 'qrc:/images/instruction/loaded-map-uber.svg',
    '': ''
  }[difficulty]

  Text {
    color: Global.primaryTextColor
    text: 'Loaded Map:'
  }
  Text {
    color: Global.primaryTextColor
    text: name
  }
}
