pragma Singleton
import QtQuick 2.8

QtObject {
  property bool plannerWindowOpen: false
  property bool puzzleWindowOpen: false
  property bool optionsWindowOpen: false
  property var lastActiveTooltipHoverArea

  property bool inLab: false
  property bool labNoteUpdaterRunning: false
  property int currentRoom: 0
  property int currentPlanIndex: 0

  property bool labNotesOutDated: false
  property bool newVersionAvailable: false


  property color backgroundColor: '#181818'
  property color primaryColor: '#212121'
  property color lightPrimaryColor: '#616161'
  property color primaryTextColor: '#FAFAFA'
  property color secondaryTextColor: '#EEEEEE'

  property var contentIconMapping: {
    'Switch puzzle': 'gauntlet-puzzle',
    'Floor puzzle': 'gauntlet-puzzle',
    'Escort gauntlet': 'gauntlet-puzzle',
    'Trap gauntlet': 'gauntlet-puzzle',
    'darkshrine': 'darkshrine',
    'argus': 'argus',
    'golden-key': 'golden-key',
    'silver-key': 'silver-key',
    'silver-door': 'silver-door'
  }

  property var nameMapping: {
    'Switch puzzle': 'Switch Puzzle',
    'Floor puzzle': 'Floor Puzzle',
    'Escort gauntlet': 'Escort Gauntlet',
    'Trap gauntlet': 'Trap Gauntlet',
    'darkshrine': 'Darkshrine',
    'argus': 'Argus',
    'golden-key': 'Golden Key',
    'golden-door': 'Golden Door',
    'silver-key': 'Silver Key',
    'silver-door': 'Silver Cache',
    'NoPhase': 'Unknown',
    'ChargeDisruptors': 'Charge Disruptors',
    'Conduits': 'Conduits',
    'Essences': 'Essences',
    'Fonts': 'Fonts',
    'Gargoyles': 'Gargoyles',
    'Idols': 'Idols',
    'Lieutenants': 'LiHeutenants',
    'Portals': 'Portals',
    'NoTrap': 'Unknown',
    'BladeSentries': 'Blade Sentries',
    'Darts': 'Darts',
    'FurnaceTraps': 'Furnace Traps',
    'Saws': 'Saws',
    'Spikes': 'Spikes',
    'SpinningBlades': 'Spinning Blades',
    'NoWeapon': 'Unknown',
    'TwoSwords': 'Two Swords',
    'SwordAndShield': 'Sword and Shield',
    'TwoHandedMace': 'Two-handed Mace'
  }
}
