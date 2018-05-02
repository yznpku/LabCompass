import QtQuick 2.8
import QtQuick.Controls 2.2
import QtQuick.Controls.Material 2.1
import QtQuick.Layouts 1.3
import com.labcompass 1.0
import '..'

WindowWithShadow {
  signal openUrl(string url)
  signal browseClientPath
  signal save

  property int contentWidth: 600
  Material.theme: Material.Dark

  property alias poeClientPath: clientPathInput.text
  property alias portalSkipsSection: portalSkipsSectionInput.checked
  property alias multiclientSupport: multiclientSupportInput.checked
  property alias uiScaleFactorIndex: uiScaleFactorInput.currentIndex

  Column {
    id: column
    width: contentWidth
    topPadding: 20
    bottomPadding: 20
    spacing: 20

    Row {
      x: 40
      height: 60
      spacing: 30
      Text {
        anchors.verticalCenter: parent.verticalCenter
        text: 'LabCompass'
        color: Global.primaryTextColor
        font.pixelSize: 32
      }
      Column {
        anchors.verticalCenter: parent.verticalCenter
        Text {
          color: Global.primaryTextColor
          text: Global.version
        }
        Row {
          MaterialInk {
            width: 32
            height: 32
            onClicked: openUrl('https://github.com/yznpku/LabCompass')
            SvgImage {
              width: 24
              height: 24
              anchors.centerIn: parent
              source: 'qrc:/images/github.svg'
            }
          }
        }
      }
      MaterialInk {
        anchors.verticalCenter: parent.verticalCenter
        width: 150
        height: 30
        visible: Global.model.newVersionAvailable
        onClicked: openUrl('https://github.com/yznpku/LabCompass/releases/tag/' + Global.model.settings.latestVersion)
        Rectangle {
          anchors.fill: parent
          color: '#2196F3'
          radius: 2
          z: -1
          Text {
            anchors.centerIn: parent
            text: 'Update Available'
            color: Global.primaryTextColor
          }
        }
        NotificationIndicator {}
      }
    }

    Rectangle {
      width: contentWidth
      height: 2
      color: Qt.lighter(Global.primaryColor)
    }

    Text {
      x: 40
      color: Global.primaryTextColor
      text: 'Options'
      font.pixelSize: 24
    }

    Item {
      width: contentWidth
      height: 30
      TextHighlightTab {
        id: tab
        anchors.fill: parent
        anchors.leftMargin: 50
        anchors.rightMargin: 50
        model: ['Client', 'UI', 'Navigation']
      }
    }

    StackLayout {
      currentIndex: tab.currentItem

      OptionsGridLayout {
        Text {
          Layout.columnSpan: 2
          color: Global.primaryTextColor
          text: 'Game Client Path'
        }
        TextField {
          id: clientPathInput
          Layout.fillWidth: true
          font.family: 'Open Sans'
        }
        MaterialInk {
          width: 32
          height: 32
          onClicked: browseClientPath();
          Image {
            anchors.centerIn: parent
            width: 24
            height: 24
            source: 'qrc:/images/browse.svg'
            sourceSize: Qt.size(96, 96)
          }
        }

        Text {
          color: Global.primaryTextColor
          text: 'Multi-client Support (Experimental)'
          font.pixelSize: 20
        }
        CheckBox {
          id: multiclientSupportInput
          width: 24
          height: 24
        }
      }

      OptionsGridLayout {
        Text {
          color: Global.primaryTextColor
          text: 'UI Scale Factor <sup>*</sup>'
          font.pixelSize: 20
        }
        ComboBox {
          id: uiScaleFactorInput
          objectName: 'uiScaleFactorInput'
        }
      }

      OptionsGridLayout {
        Text {
          color: Global.primaryTextColor
          text: 'Taking Portals Skips Current Section'
          font.pixelSize: 20
        }
        CheckBox {
          id: portalSkipsSectionInput
          width: 24
          height: 24
        }
      }
    }

    Text {
      x: 40
      color: Global.secondaryTextColor
      text: '<sup>*</sup> Restart LabCompass to Apply Changes'
      font.pixelSize: 16
    }
  }

  MaterialInk {
    id: closeButton
    width: 40
    height: 40
    anchors.right: column.right
    anchors.rightMargin: 10
    anchors.top: column.top
    anchors.topMargin: 10
    onClicked: Global.optionsWindowOpen = false;
    SvgImage {
      anchors.centerIn: parent
      source: 'qrc:/images/close.svg'
    }
  }

  MaterialInk {
    id: saveButton
    anchors.right: column.right
    anchors.rightMargin: 30
    anchors.bottom: column.bottom
    anchors.bottomMargin: 15
    width: 80
    height: 30
    onClicked: {
      save();
      Global.optionsWindowOpen = false;
    }
    Rectangle {
      anchors.fill: parent
      color: '#2196F3'
      radius: 2
      z: -1
      Text {
        anchors.centerIn: parent
        text: 'OK'
        color: Global.primaryTextColor
      }
    }
  }
}
