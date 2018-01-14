import QtQuick 2.8
import com.labcompass 1.0

WindowWithShadow {
  property int switchModel: 0
  property int guideModel: 0

  Item {
    id: root
    width: 300
    height: 200

    Item {
      anchors.centerIn: parent
      Repeater {
        id: switchView
        model: 8
        Item {
          x: [-1, -0.5, 0, 0.5, 1, 0.5, 0, -0.5][index] * 90
          y: [0, -0.5, -1, -0.5, 0, 0.5, 1, 0.5][index] * 60

          Rectangle {
            width: 20
            height: 20
            radius: 10
            anchors.centerIn: parent
            color: 'transparent'
            border { width: 2; color: Global.primaryTextColor }
          }

          Rectangle {
            id: activeIndicator
            x: -width / 2
            y: -height / 2
            color: Global.primaryTextColor
            state: switchModel & (1 << index) ? 'active' : 'inactive'
            states: [
              State { name: 'active'; PropertyChanges { target: activeIndicator; width: 10; height: 10; radius: 5 }},
              State { name: 'inactive'; PropertyChanges { target: activeIndicator; width: 0; height: 0; radius: 0 }}
            ]
            transitions: Transition {
              NumberAnimation {
                properties: 'width,height,radius'
                easing.type: Easing.Bezier
                easing.bezierCurve: [0.4, 0.0, 0.2, 1.0, 1.0, 1.0]
                duration: 100
              }
            }
          }

          Item {
            id: guideFocus
            property real visibility
            Repeater {
              model: 4
              Item {
                x: [-1, 1, 1, -1][index] * (30 - 15 * guideFocus.visibility)
                y: [-1, -1, 1, 1][index] * (30 - 15 * guideFocus.visibility)
                opacity: guideFocus.visibility
                Image {
                  anchors.centerIn: parent
                  rotation: index * 90
                  source: 'qrc:/images/rounded-corner.png'
                }
              }
            }
            state: guideModel & (1 << index) ? 'active' : 'inactive'
            states: [
              State { name: 'active'; PropertyChanges { target: guideFocus; visibility: 1 }},
              State { name: 'inactive'; PropertyChanges { target: guideFocus; visibility: 0 }}
            ]
            transitions: Transition {
              NumberAnimation {
                properties: 'visibility'
                easing.type: Easing.Bezier
                easing.bezierCurve: [0.4, 0.0, 0.2, 1.0, 1.0, 1.0]
                duration: 100
              }
            }
          }

          MouseArea {
            anchors.centerIn: parent
            width: 32
            height: 32
            cursorShape: Qt.PointingHandCursor
            onClicked: {
              switchModel = switchModel ^ (1 << index);
              guideModel = 0;
            }
          }
        }
      }

      MaterialInk {
        width: 32
        height: 32
        anchors.centerIn: parent
        onClicked: guideModel = [255, 146, 37, 72, 74, 39, 144, 253, 148, 249, 78, 35, 33, 76, 251, 150, 41, 68, 243, 158, 156, 241, 70, 43, 66, 47, 152, 245, 247, 154, 45, 64, 82, 63, 136, 229, 231, 138, 61, 80, 57, 84, 227, 142, 140, 225, 86, 59, 132, 233, 94, 51, 49, 92, 235, 134, 239, 130, 53, 88, 90, 55, 128, 237, 164, 201, 126, 19, 17, 124, 203, 166, 207, 162, 21, 120, 122, 23, 160, 205, 114, 31, 168, 197, 199, 170, 29, 112, 25, 116, 195, 174, 172, 193, 118, 27, 9, 100, 211, 190, 188, 209, 102, 11, 98, 15, 184, 213, 215, 186, 13, 96, 223, 178, 5, 104, 106, 7, 176, 221, 180, 217, 110, 3, 1, 108, 219, 182, 73, 36, 147, 254, 252, 145, 38, 75, 34, 79, 248, 149, 151, 250, 77, 32, 159, 242, 69, 40, 42, 71, 240, 157, 244, 153, 46, 67, 65, 44, 155, 246, 228, 137, 62, 83, 81, 60, 139, 230, 143, 226, 85, 56, 58, 87, 224, 141, 50, 95, 232, 133, 135, 234, 93, 48, 89, 52, 131, 238, 236, 129, 54, 91, 18, 127, 200, 165, 167, 202, 125, 16, 121, 20, 163, 206, 204, 161, 22, 123, 196, 169, 30, 115, 113, 28, 171, 198, 175, 194, 117, 24, 26, 119, 192, 173, 191, 210, 101, 8, 10, 103, 208, 189, 212, 185, 14, 99, 97, 12, 187, 214, 105, 4, 179, 222, 220, 177, 6, 107, 2, 111, 216, 181, 183, 218, 109, 0][switchModel]
        SvgImage {
          width: 24
          height: 24
          source: 'qrc:/images/focus.svg'
          anchors.centerIn: parent
        }
      }
    }
    MaterialInk {
      id: closeButton
      width: 40
      height: 40
      anchors.right: parent.right
      anchors.rightMargin: 10
      anchors.top: parent.top
      anchors.topMargin: 10
      onClicked: Global.puzzleWindowOpen = false;
      SvgImage {
        anchors.centerIn: parent
        source: 'qrc:/images/close.svg'
      }
    }
  }
}
