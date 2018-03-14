pragma Singleton
import QtQuick 2.8

QtObject {
  property string version
  property bool debug: false

  property bool plannerWindowOpen: false
  property bool puzzleWindowOpen: false
  property bool optionsWindowOpen: false
  property var lastActiveTooltipHoverArea

  property var model

  property color backgroundColor: '#181818'
  property color primaryColor: '#212121'
  property color lightPrimaryColor: '#616161'
  property color primaryTextColor: '#FAFAFA'
  property color secondaryTextColor: '#A0A0A0'

  property color activePathColor: '#8BC34A'
  property color inactivePathColor: '#404440'

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
    'Lieutenants': 'Lieutenants',
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

  property var directionMapping: {
    'N': {
      name: 'North',
      rotation: 0,
      dx: 0,
      dy: -1
    },
    'NE': {
      name: 'Northeast',
      rotation: 45,
      dx: 0.71,
      dy: -0.71
    },
    'E': {
      name: 'East',
      rotation: 90,
      dx: 1,
      dy: 0
    },
    'SE': {
      name: 'Southeast',
      rotation: 135,
      dx: 0.71,
      dy: 0.71
    },
    'S': {
      name: 'South',
      rotation: 180,
      dx: 0,
      dy: 1
    },
    'SW': {
      name: 'Southwest',
      rotation: 225,
      dx: -0.71,
      dy: 0.71,
    },
    'W': {
      name: 'West',
      rotation: 270,
      dx: -1,
      dy: 0
    },
    'NW': {
      name: 'Northwest',
      rotation: 315,
      dx: -0.71,
      dy: -0.71
    }
  }
}
