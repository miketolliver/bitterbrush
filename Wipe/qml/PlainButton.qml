import QtQuick 1.1

Rectangle {
    id: btnRoot

    width: btnText.paintedWidth + (btnText.paintedHeight * 2);
    height: btnText.paintedHeight * 3;

    property bool pPressed: btnMouseArea.pressed;
    property color pBgColor: "#F6F6F6"
    property color pBgColorPressed: "#DDDDDD"
    property color pTextColor: "#888888"
    property string pText: "Plain Button"
    property color pBorderColor: "#888888"
    property int pBorderSize: 0;
    property int pTextPointSize: wipeLogic.getFontPointSizeM();


    signal btnClicked();

    color: pPressed ? pBgColorPressed : pBgColor;
    border.color: pBorderColor;
    border.width: pBorderSize;


    Text{
        id: btnText
        anchors.fill: parent;

        text: qsTr(pText);
        color: pTextColor;
        font.pointSize: pTextPointSize;
        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignVCenter
    }

    MouseArea{
        id: btnMouseArea
        anchors.fill: parent;
        onClicked: {
            btnClicked();
        }
    }

}

