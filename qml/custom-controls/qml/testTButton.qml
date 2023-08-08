import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.12

import TControls 1.0

TWindow {
    width: btnRow.width + 60; height: 600

    Row {
        id: btnRow
        spacing: 10
        anchors.left: parent.left
        anchors.top: parent.top
        anchors.margins: 10

        TButton {
            id: tBtn
            text: "border btn"
            iconSource: "/images/zidytubiao.svg"
            font.pointSize: 14
            showBorder: true
            backRadius: height / 4
        }

        TButton {
            text: "shadow btn"
            iconSource: "/images/zidytubiao.svg"
            font.pointSize: 14
            // showBorder: true
            backRadius: height / 4
            elevation: height / 2
        }

        TButton {
            font.pointSize: 14
        }
    }

    Column {
        anchors.top: btnRow.bottom
        anchors.topMargin: 20
        anchors.right: parent.right

        Button {
            text: "change Left"
            onClicked: {
                tBtn.iconPos = TButton.IconPos.Left
            }
        }
        Button {
            text: "change Right"
            onClicked: {
                tBtn.iconPos = TButton.IconPos.Right
            }
        }
        Button {
            text: "change Top"
            onClicked: {
                tBtn.iconPos = TButton.IconPos.Top
            }
        }
        Button {
            text: "change Bottom"
            onClicked: {
                tBtn.iconPos = TButton.IconPos.Bottom
            }
        }
    }
}
