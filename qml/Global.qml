pragma Singleton
import QtQuick 2.8

QtObject {
  property bool plannerWindowOpen: false

  property bool inLab: false
  property bool labNoteUpdaterRunning: false


  property color backgroundColor: '#181818'
  property color primaryColor: '#212121'
  property color lightPrimaryColor: '#F5F5F5'
  property color primaryTextColor: '#FAFAFA'
  property color secondaryTextColor: '#EEEEEE'

  property var contentIconMapping: {
    'Switch puzzle': 'gauntlet-puzzle',
    'Floor puzzle': 'gauntlet-puzzle',
    'Escort gauntlet': 'gauntlet-puzzle',
    'Trap gauntlet': 'gauntlet-puzzle',
    'darkshrine': 'darkshrine',
    'argus': 'argus'
  }
}
