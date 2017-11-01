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
    active: Global && Global.puzzleWindowOpen
    onClicked: {
      if (Global) {
        var open = Global.puzzleWindowOpen;
        closeAllWindows();
        if (!open)
          Global.puzzleWindowOpen = true;
      }
    }
  }

  ToolbarButton {
    height: 40
    source: '../images/settings.png'
    active: Global && Global.optionsWindowOpen
    onClicked: {
      if (Global) {
        var open = Global.optionsWindowOpen;
        closeAllWindows();
        if (!open)
          Global.optionsWindowOpen = true;
      }
    }
  }

  function closeAllWindows() {
    Global.plannerWindowOpen = false;
    Global.puzzleWindowOpen = false;
    Global.optionsWindowOpen = false;
  }
}
