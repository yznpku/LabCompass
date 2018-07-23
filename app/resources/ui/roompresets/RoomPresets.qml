import QtQuick 2.8
import com.labcompass 1.0
import '..'

WindowWithShadow {
  id: window
  property var roomPresetModel: Global.model.roomPresetModel
  property alias presetListViewCurrentIndex: presetListView.currentIndex

  signal drag(int dx, int dy)
  signal applyPresetButtonClicked(string areaCode)

  Column {
    id: grid
    spacing: 20
    topPadding: 20
    bottomPadding: 20
    width: 900

    Item {
      height: 50
      width: grid.width

      DragMoveArea {
        x: 20
        width: 350
        height: 80
        anchors.verticalCenter: parent.verticalCenter
        onDrag: window.drag(dx, dy)

        Text {
          text: 'Room Layout Presets'
          anchors.centerIn: parent
          color: Global.primaryTextColor
          font.pixelSize: 32
        }
      }

      MaterialInk {
        id: closeButton
        width: 40
        height: 40
        anchors.right: parent.right
        anchors.rightMargin: 20
        anchors.top: parent.top
        onClicked: Global.roomPresetsWindowOpen = false;
        SvgImage {
          anchors.centerIn: parent
          source: 'qrc:/images/close.svg'
        }
      }
    }

    Rectangle {
      width: grid.width
      height: 2
      color: Qt.lighter(Global.primaryColor)
    }

    Item {
      width: grid.width
      height: 480

      Rectangle {
        id: presetList
        width: 240
        anchors {
          left: parent.left
          top: parent.top
          bottom: parent.bottom
          leftMargin: 30
        }
        color: Global.primaryColor

        ListView {
          id: presetListView
          anchors.fill: parent
          clip: true
          model: roomPresetModel.presets
          highlightFollowsCurrentItem: false
          delegate: Item {
            width: 240
            height: 120

            Grid {
              anchors.centerIn: parent
              columns: 1
              horizontalItemAlignment: Grid.AlignHCenter
              StaticMinimapDisplay {
                width: 90
                height: width / 1.3
                presetModel: modelData
              }
              Text {
                color: Global.primaryTextColor
                text: modelData.areaCode
              }
            }
            SvgImage {
              anchors.top: parent.top
              anchors.right: parent.right
              width: 32
              height: 32
              source: 'qrc:/images/check.svg'
              visible: roomPresetModel.current === index
            }

            MouseArea {
              anchors.fill: parent
              cursorShape: Qt.PointingHandCursor
              onClicked: presetListView.currentIndex = index
            }
          }
          highlight: Rectangle {
            y: presetListView.currentItem ? presetListView.currentItem.y : 0
            width: 240
            height: 120
            color: '#373737'
          }
        }
      }

      Item {
        id: presetDetails
        anchors {
          left: presetList.right
          top: parent.top
          right: parent.right
          bottom: buttonArea.top
          leftMargin: 20
          rightMargin: 30
          bottomMargin: 20
        }

        Loader {
          active: window.state === ''
          anchors.fill: parent
          sourceComponent: Item {
            property var model: roomPresetModel.presets[presetListView.currentIndex]
            Item {
              id: presetName
              anchors {
                left: parent.left
                top: parent.top
                right: parent.right
              }
              height: 60
              Text {
                x: 20
                anchors.verticalCenter: parent.verticalCenter
                text: model ? roomPresetModel.roomName + ' > ' + model.areaCode : ''
                font.pixelSize: 24
                color: Global.primaryTextColor
              }
            }
            Row {
              anchors {
                top: presetName.bottom
                bottom: parent.bottom
                horizontalCenter: parent.horizontalCenter
              }
              StaticMinimapDisplay {
                width: 416
                height: 320
                presetModel: model
              }
              MinimapLegend {
                anchors.verticalCenter: parent.verticalCenter
              }
            }
          }
        }

        Loader {
          active: window.state === 'NoPresets'
          anchors.fill: parent
          sourceComponent: Item {
            Text {
              anchors.centerIn: parent
              font.pixelSize: 24
              color: Global.primaryTextColor
              text: 'No Presets Available for This Room'
            }
          }
        }

        Loader {
          active: window.state === 'Disabled'
          anchors.fill: parent
          sourceComponent: Item {
            Text {
              anchors.centerIn: parent
              font.pixelSize: 24
              color: Global.primaryTextColor
              text: 'Presets Will Be Disabled for This Room'
            }
          }
        }
      }

      Item {
        id: buttonArea
        anchors {
          left: presetList.right
          right: parent.right
          bottom: parent.bottom
          leftMargin: 20
          rightMargin: 30
        }
        height: 80

        MaterialInk {
          width: 220
          height: 40
          anchors.centerIn: parent
          visible: (window.state === '' || window.state === 'Disabled') && presetListView.currentIndex !== roomPresetModel.current
          onClicked: applyPresetButtonClicked(roomPresetModel.presets[presetListView.currentIndex].areaCode)
          Rectangle {
            anchors.fill: parent
            color: Global.accentColor
            radius: 2
            z: -1
            Text {
              anchors.centerIn: parent
              text: 'Apply Preset'
              color: Global.primaryTextColor
            }
          }
        }
      }
    }
  }

  states: [
    State {
      name: 'NoPresets'
      when: roomPresetModel.presets.length === 0
    },
    State {
      name: 'NotSelected'
      when: presetListView.currentIndex === -1
    },
    State {
      name: 'Disabled'
      when: presetListView.currentIndex === presetListView.count - 1
    }
  ]
}
