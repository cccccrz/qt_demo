import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.12

import TControls 1.0
import ScreenTools 1.0
import QGroundControl.Palette 1.0

TWindow {
    id: _root
    minimumWidth: 400; minimumHeight: 600

    Component.onCompleted: {
        console.log(ScreenTools.isAndroid)
        console.log(ScreenTools.defaultFontPixelWidth)
        console.log(qgcPal.text, qgcPal.button, qgcPal.buttonHighlightTextColors)
    }

    QGCPalette { id: qgcPal }

    Flickable {
        anchors.margins: ScreenTools.defaultFontPixelWidth
        anchors.fill: parent
        contentWidth: parent.width - 20
        contentHeight: _mainLayout.height

        ListModel {
            id: _listModel
            ListElement { name: "Option 1" }
            ListElement { name: "Option 2" }
            ListElement { name: "Option 3" }
        }

        Grid {
            id: _mainLayout
            spacing: 20
            columns: 2
            anchors.centerIn: parent

            BusyIndicator { }
            TBusyIndicator { }

            CheckBox {}
            TCheckBox {}

            ComboBox { model: _listModel }
            TComboBox { model: _listModel }

            ListView {
                width: 120; height: 140
                model: _listModel
                delegate: CheckDelegate {
                    text: modelData
                }
                clip: true
            }

            ListView {
                width: 120; height: 140
                model: _listModel
                delegate: TCheckDelegate {
                    text: modelData
                }
                clip: true
            }

            DelayButton {}
            TDelayButton {}

            Dial {}
            TDial {}
        }
    }
}
