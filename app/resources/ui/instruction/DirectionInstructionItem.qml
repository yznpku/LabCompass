import QtQuick 2.8
import com.labcompass 1.0

InstructionItem {
  id: root

  property string connectionType
  property string direction
  property string nextRoomName
  property bool atPlaza
  property bool nextRoomIsPreviousRoom
  property bool nextRoomIsUnmarkedOppositeDirection

  iconSource: connectionType == 'secret' ? 'qrc:/images/instruction/secret-passage.svg' :
              direction in Global.directionMapping ? 'qrc:/images/instruction/direction_' + direction + '.svg' :
              nextRoomIsPreviousRoom ? 'qrc:/images/instruction/backward.svg' :
              nextRoomIsUnmarkedOppositeDirection ? 'qrc:/images/instruction/opposite.svg' :
              'qrc:/images/instruction/direction_unknown.svg'

  Text {
    visible: atPlaza
    color: Global.primaryTextColor
    text: 'Enter the Labyrinth'
  }

  Text {
    visible: !atPlaza
    color: Global.primaryTextColor
    text: nextRoomIsPreviousRoom ? 'Back to Previous Room' :
          direction in Global.directionMapping ? Global.directionMapping[direction].name + ' Exit' :
          connectionType == 'secret' ? 'Secret Passage' :
          nextRoomIsUnmarkedOppositeDirection ? 'Opposite Exit' :
          'Unmarked Exit'
  }

  Text {
    visible: !atPlaza
    color: Global.primaryTextColor
    text: (nextRoomIsPreviousRoom ? '' : 'To ') + nextRoomName
  }
}
