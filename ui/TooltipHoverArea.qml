import QtQuick 2.8
import com.labcompass 1.0

MouseArea {
  id: root
  property bool shouldDisplayTooltip: false
  hoverEnabled: true

  onContainsMouseChanged: {
    if (containsMouse) {
      exitTimer.stop();
      if (Global.lastActiveTooltipHoverArea && Global.lastActiveTooltipHoverArea.shouldDisplayTooltip) {
        Global.lastActiveTooltipHoverArea.shouldDisplayTooltip = false;
        shouldDisplayTooltip = true;
        Global.lastActiveTooltipHoverArea = root;
      } else {
        enterTimer.restart();
      }
    } else {
      enterTimer.stop();
      exitTimer.restart();
    }
  }
  onPressed: {
    enterTimer.stop();
    shouldDisplayTooltip = false;
    mouse.accepted = false;
  }

  Timer {
    id: enterTimer
    interval: 800
    onTriggered: {
      shouldDisplayTooltip = true;
      Global.lastActiveTooltipHoverArea = root;
    }
  }
  Timer {
    id: exitTimer
    interval: 300
    onTriggered: {
      shouldDisplayTooltip = false;
    }
  }
}
