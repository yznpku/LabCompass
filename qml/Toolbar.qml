import QtQuick 2.8
import com.labcompass 1.0

Row {
  id: root
  spacing: 4

  ToolbarButton {
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
    source: '../images/puzzle.png'
  }

  ToolbarButton {
    source: '../images/pencil.png'
  }

  ToolbarButton {
    source: '../images/settings.png'
  }

  function closeAllWindows() {
    Global.plannerWindowOpen = false;
  }
}
