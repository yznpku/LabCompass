import QtQuick 2.8
import com.labcompass 1.0

Column {
  id: root
  spacing: 4

  ToolbarButton {
    height: 40
    source: '../images/navigation.png'
    active: Global && Global.plannerWindowOpen
    onClicked: {
      if (Global) {
        var open = Global.plannerWindowOpen;
        closeAllWindows();
        if (!open)
          Global.plannerWindowOpen = true;
      }
    }
  }

  ToolbarButton {
    height: 40
    source: '../images/puzzle.png'
  }

  ToolbarButton {
    height: 40
    source: '../images/settings.png'
  }

  function closeAllWindows() {
    Global.plannerWindowOpen = false;
  }
}
