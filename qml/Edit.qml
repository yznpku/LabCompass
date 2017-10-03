import QtQuick 2.8

Grid {
  columns: 4
  spacing: 4

  signal exitDirection(string dir)
  signal contentDirection(string dir)
  signal content(string name)
  signal clearMap
  signal iterateNext
  signal save

  ToolbarButton {
    source: '../images/arrow-top-left.png'
    onClicked: exitDirection('NW')
  }

  ToolbarButton {
    source: '../images/arrow-up.png'
    onClicked: exitDirection('N')
  }

  ToolbarButton {
    source: '../images/arrow-top-right.png'
    onClicked: exitDirection('NE')
  }

  ToolbarButton {
    source: '../images/delete.png'
    onClicked: clearMap()
  }

  ToolbarButton {
    source: '../images/arrow-left.png'
    onClicked: exitDirection('W')
  }

  ToolbarButton {
    source: '../images/arrow-down-bold-hexagon-outline.png'
    onClicked: exitDirection('C')
  }

  ToolbarButton {
    source: '../images/arrow-right.png'
    onClicked: exitDirection('E')
  }

  ToolbarButton {
    source: '../images/arrow-right-drop-circle-outline.png'
    onClicked: iterateNext()
  }

  ToolbarButton {
    source: '../images/arrow-bottom-left.png'
    onClicked: exitDirection('SW')
  }

  ToolbarButton {
    source: '../images/arrow-down.png'
    onClicked: exitDirection('S')
  }

  ToolbarButton {
    source: '../images/arrow-bottom-right.png'
    onClicked: exitDirection('SE')
  }

  ToolbarButton {
    source: '../images/save.png'
    onClicked: save()
  }

  ToolbarButton {
    source: '../images/lab-content/argus.png'
    onClicked: content('argus')
  }

  ToolbarButton {
    source: '../images/lab-content/darkshrine.png'
    onClicked: content('darkshrine')
  }

  ToolbarButton {
    source: '../images/lab-content/gauntlet.png'
    onClicked: content('gauntlet')
  }

  ToolbarButton {
    source: '../images/lab-content/puzzle.png'
    onClicked: content('puzzle')
  }

  ToolbarButton {
    source: '../images/arrow-top-left.png'
    onClicked: contentDirection('NW')
  }

  ToolbarButton {
    source: '../images/arrow-up.png'
    onClicked: contentDirection('N')
  }

  ToolbarButton {
    source: '../images/arrow-top-right.png'
    onClicked: contentDirection('NE')
  }

  ToolbarButton {
    source: '../images/lab-content/golden-key.png'
    onClicked: content('golden-key')
  }

  ToolbarButton {
    source: '../images/arrow-left.png'
    onClicked: contentDirection('W')
  }

  Item { width: 1; height: 1 }

  ToolbarButton {
    source: '../images/arrow-right.png'
    onClicked: contentDirection('E')
  }

  ToolbarButton {
    source: '../images/lab-content/silver-key.png'
    onClicked: content('silver-key')
  }

  ToolbarButton {
    source: '../images/arrow-bottom-left.png'
    onClicked: contentDirection('SW')
  }

  ToolbarButton {
    source: '../images/arrow-down.png'
    onClicked: contentDirection('S')
  }

  ToolbarButton {
    source: '../images/arrow-bottom-right.png'
    onClicked: contentDirection('SE')
  }

  ToolbarButton {
    source: '../images/lab-content/silver-door.png'
    onClicked: content('silver-door')
  }
}
