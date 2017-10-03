import QtQuick 2.8
import com.labcompass 1.0

Row {
  id: root
  spacing: 4

  ToolbarButton {
    source: '../images/navigation.png'
    active: Global && Global.plannerWindowOpen
    onClicked: if (Global) Global.plannerWindowOpen = !Global.plannerWindowOpen
  }

  ToolbarButton {
    source: '../images/puzzle.png'
  }

  ToolbarButton {
    source: '../images/pencil.png'
    active: Global && Global.editWindowOpen
    onClicked: if (Global) Global.editWindowOpen = !Global.editWindowOpen
  }

  ToolbarButton {
    source: '../images/settings.png'
  }
}
