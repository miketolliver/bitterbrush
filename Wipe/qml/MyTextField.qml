import QtQuick 1.1

Rectangle {
    width: 100
    height: Math.round(placeholderText.paintedHeight * 1.25)

    color: "transparent";
    //color: "#22191919"

    property string pPlaceHolderText: "";
    property color pTextColor: "#4b4b4b";
    property color pPlaceholderTextColor: "#7b7b7b";
    property bool pIsPw: false;
    property alias pEnteredText: textInput.text;
    property alias pTextInput: textInput;

    Text{
        id: placeholderText;
        anchors.fill: textInput;
        text: pPlaceHolderText
        color: pPlaceholderTextColor
        visible: !textInput.activeFocus; //textInput.displayText.length <= 0;
        font.pointSize: wipeLogic.getFontPointSizeM2();
        //font: textInput.font;
        //opacity: 0.5;
        verticalAlignment: Text.AlignHCenter
    }

    TextInput{
        id: textInput
        anchors.left: parent.left;
        anchors.right: parent.right;
        anchors.leftMargin: Math.round(placeholderText.paintedHeight * 0.25)
        anchors.verticalCenter: parent.verticalCenter;
        color: pTextColor;
        text: "";
        font.pointSize: wipeLogic.getFontPointSizeM2();
        //echoMode: pIsPw ? TextInput.Password : TextInput.Normal;
        echoMode: TextInput.Password;

    }

    Rectangle{
        id: footerLine
        anchors.left: parent.left
        anchors.right: parent.right;
        anchors.top: parent.bottom
        height: textInput.activeFocus ? 2 : 1;
        color: textInput.activeFocus ? "#009688" : "#757575"

    }

}

