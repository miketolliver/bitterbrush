import QtQuick 1.1

Rectangle {
    id: btnRoot

    width: 48
    height: 48

    property bool pPressed: btnMouseArea.pressed;
    property color pBgColor: "transparent"
    property color pBgColorPressed: "#DDDDDD"
    property color pBorderColor: "#888888"
    property int pBorderSize: 0;
    property string pIconSrc: "";

    signal btnClicked();

    color: pPressed ? pBgColorPressed : pBgColor;
    border.color: pBorderColor;
    border.width: pBorderSize;

    Image{
        id: btnImage
        //anchors.fill: parent;
        //anchors.margins: Math.round(parent.height*0.25)
        anchors.centerIn: parent;
        width: Math.min(sourceSize.width, parent.width);
        height: Math.min(sourceSize.height, parent.height);
        source: pIconSrc;
        //fillMode: Image.PreserveAspectFit
        fillMode: Image.PreserveAspectFit
    }

    MouseArea{
        id: btnMouseArea
        anchors.fill: parent;
        onClicked: {
            btnClicked();
        }
    }

}

