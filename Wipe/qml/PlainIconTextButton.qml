import QtQuick 1.1

Rectangle {
    id: btnRoot

    width: btnText.paintedWidth + btnImage.paintedWidth + (btnText.paintedHeight * 3);
    height: Math.round(btnText.paintedHeight * 2.5);

    property bool pPressed: btnMouseArea.pressed;
    property color pBgColor: "transparent"
    property color pBgColorPressed: "#DDDDDD"
    property color pBorderColor: "#888888"
    property int pBorderSize: 0;
    property string pIconSrc: "";
    property color pTextColor: "#888888"
    property string pText: "Plain Button"
    property int pTextPointSize: wipeLogic.getFontPointSizeM();

    signal btnClicked();

    color: pPressed ? pBgColorPressed : pBgColor;
    border.color: pBorderColor;
    border.width: pBorderSize;

    Image{
        id: btnImage
        anchors.left: parent.left
        anchors.verticalCenter: parent.verticalCenter;
        anchors.leftMargin: Math.round(btnText.paintedHeight/2);
        //width: Math.min(sourceSize.width, parent.width);
        height: Math.min(sourceSize.height, Math.round(btnText.paintedHeight*1.25));
        //height: sourceSize.height;
        source: pIconSrc;
        fillMode: Image.PreserveAspectFit
        smooth: true;
    }

    Text{
        id: btnText
        anchors.left: btnImage.right;
        anchors.leftMargin: Math.round(paintedHeight/2);
        anchors.verticalCenter: parent.verticalCenter;
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

