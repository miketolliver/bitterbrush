import QtQuick 1.1

Rectangle {
    width: settingsBtn.width
    height: 62
    color: "#282828"

    Text{
        id: spacer
        font.pointSize: wipeLogic.getFontPointSizeM();
        text: "T"
        visible: false;
    }

    Rectangle{
        id: drawerHeader
        anchors.left: parent.left;
        anchors.right: parent.right;
        anchors.top: parent.top;
        height: Math.round(headerImg.paintedHeight * 1.3);

        color: "#1e1e1e";


        Image{
            id: headerImg
            anchors.left: parent.left;
            anchors.leftMargin: spacer.paintedHeight;
            anchors.verticalCenter: parent.verticalCenter;
            width: height;
            height: Math.min(sourceSize.height, Math.round(headerTxt.paintedHeight*1.25));
            source: "qrc:/images/ic_nuke.png"
            fillMode: Image.PreserveAspectFit
            smooth: true;
        }
        Text{
            id: headerTxt
            anchors.left: headerImg.right
            anchors.leftMargin: spacer.paintedHeight;
            anchors.right: parent.right;
            anchors.verticalCenter: parent.verticalCenter;

            color: "#ffffff"
            text: qsTr("Wipe");
            font.pointSize: wipeLogic.getFontPointSizeL();
            //font.bold: true;
        }

    }

    PlainButton{
        id: settingsBtn
        anchors.top: drawerHeader.bottom;

        pBgColor: "#282828"
        pBgColorPressed: "#1e1e1e"
        pTextPointSize: wipeLogic.getFontPointSizeM2();
        pTextColor: "#ffffff"
        pText: qsTr("  Remote Settings   ");
    }




    PlainButton{
        id: backBtn
        anchors.bottom: parent.bottom;
        anchors.left: parent.left

        pBgColor: "#282828"
        pBgColorPressed: "#1e1e1e"
        pTextPointSize: wipeLogic.getFontPointSizeM2();
        pTextColor: "#ffffff"
        pText: qsTr("Back ");
    }

}

