import QtQuick 2.8
import QtQuick.Controls 2.2
import QtQuick.Controls.Material 2.1
import QtQuick.Layouts 1.3
import com.labcompass 1.0

Button {
  id: root

  Layout.minimumWidth: 200

  property alias modifierlessAllowed: helper.modifierlessAllowed
  property alias multiKeyShortcutsAllowed: helper.multiKeyShortcutsAllowed
  property alias keySequence: helper.keySequence

  KeySequenceHelper {
    id: helper
    modifierlessAllowed: true
    onCaptureFinished: focus = false;
  }

  checkable: true
  focus: checked
  text: helper.shortcutDisplay

  onClicked: {
    if (!checked) {
      helper.cancelRecording();
    }
  }

  onCheckedChanged: {
    if (checked) {
      forceActiveFocus();
      helper.captureKeySequence();
    }
  }

  onFocusChanged: {
    if (!focus) {
      checked = false;
    }
  }

  Keys.onPressed: {
    helper.keyPressed(event.key, event.modifiers);
    event.accepted = true;
  }
  Keys.onReleased: {
    helper.keyReleased(event.key, event.modifiers);
    event.accepted = true;
  }
}
