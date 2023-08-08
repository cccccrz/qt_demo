import QtQuick 2.12
import QtQuick.Controls 2.12
import QtGraphicalEffects 1.0

Button {
    id:             _control
    text:           "TButton"
    topPadding:      _verticalPadding
    bottomPadding:   _verticalPadding
    leftPadding:     _horizontalPadding
    rightPadding:    _horizontalPadding
    focusPolicy:     Qt.ClickFocus
    spacing:         10

    // button style
    property int backRadius: 0
    property bool showBorder:           false
    property bool showHighLight:        pressed | hovered | checked
    property color backColor:           "gainsboro"
    property color backHighLightColor:  "white"
    property color borderColor:         "gray"
    property color borderHighLightColor: "lawngreen"
    property color textColor:           "black"
    property color textHighLightColor:  "cornflowerblue"
    property int _verticalPadding:      10
    property int _horizontalPadding:    10
    // shadow
    property int elevation: 0
    // icon text position
    enum IconPos {
        Left,
        Right,
        Top,
        Bottom
    }
    property int iconPos: TButton.IconPos.Left
    property string iconSource: ""

    // debug
    onClicked: {
        console.log(_control.text, "clicked")
    }

    contentItem: Item {
        implicitHeight: (iconPos === TButton.IconPos.Left || iconPos === TButton.IconPos.Right)
                        ? _text.implicitHeight : _text.implicitHeight + _icon.implicitHeight + _control.spacing
        implicitWidth: (iconPos === TButton.IconPos.Left || iconPos === TButton.IconPos.Right)
                       ? _icon.implicitWidth + _text.implicitWidth + _control.spacing : Math.max(_text.implicitWidth, _icon.implicitWidth)
        //        baselineOffset: _text.y + _text.baselineOffset

        Image {
            id: _icon
            source: _control.iconSource
            fillMode: Image.PreserveAspectFit
            height: iconSource === "" ? 0 : _text.height
            width: height
            sourceSize.height: height
            // pos
            anchors.left: iconPos === TButton.IconPos.Right ? _text.right : parent.left
            anchors.leftMargin: iconPos === TButton.IconPos.Right ? _control.spacing : 0

            anchors.top: iconPos === TButton.IconPos.Bottom ? _text.bottom : parent.top
            anchors.topMargin: iconPos === TButton.IconPos.Bottom ? _control.spacing : 0
        }
        Text {
            id: _text
            text: _control.text
            antialiasing: true
            color: showHighLight ? textHighLightColor : textColor
            // font style ...
            font: _control.font
            // pos
            anchors.left: iconPos === TButton.IconPos.Left ? _icon.right : parent.left
            anchors.leftMargin: iconPos === TButton.IconPos.Left ? _control.spacing : 0

            anchors.top: iconPos === TButton.IconPos.Top ? _icon.bottom : parent.top
            anchors.topMargin: iconPos === TButton.IconPos.Top ? _control.spacing : 0
        }
    }

    background: Rectangle {
        implicitWidth:  40
        implicitHeight: 15
        border.width: showBorder ? 1 : 0
        border.color: showHighLight ? borderHighLightColor : borderColor
        color: showHighLight ?  backHighLightColor : backColor
        radius: backRadius

        // shadow style
        layer.enabled: _control.elevation > 0
        layer.effect: DropShadow {
            // verticalOffset: 1
            color: _control.visualFocus ? "#330066ff" : "#aaaaaa"
            samples: _control.elevation
            spread: 0.5
        }
    }
}
