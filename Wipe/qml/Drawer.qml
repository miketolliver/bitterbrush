import QtQuick 1.1

Rectangle {
    width: settingsBtn.width
    height: 62
    color: "#282828"

    signal closeDrawer();
    signal openSettings();

    MouseArea{
        id: bgMouseArea
        anchors.fill: parent;
        onClicked: {

        }
    }

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
        height: Math.round(headerImg.paintedHeight * 1.65);

        color: "#1e1e1e";


        Image{
            id: headerImg
            anchors.left: parent.left;
            anchors.leftMargin: Math.round(spacer.paintedHeight*0.33);
            anchors.verticalCenter: parent.verticalCenter;
            width: height;
            height: Math.min(sourceSize.height, Math.round(headerTxt.paintedHeight*1.35));
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

    PlainIconTextButton{
        id: settingsBtn
        anchors.top: drawerHeader.bottom;

        pBgColor: "#282828"
        pBgColorPressed: "#1e1e1e"
        pTextPointSize: wipeLogic.getFontPointSizeM();
        pTextColor: "#ffffff"
        pText: qsTr("  Remote Settings    ");
        pIconSrc: "qrc:/images/menu_setting.png"
        onBtnClicked: openSettings();
    }

    Rectangle{
        id: line1
        anchors.top: settingsBtn.bottom
        anchors.left: parent.left;
        anchors.right: parent.right;
        height: 2;
        color: "#1e1e1e"
    }

    PlainIconTextButton{
        id: backBtn
        anchors.bottom: parent.bottom;
        anchors.left: parent.left;
        anchors.right: parent.right;

        pBgColor: "#282828"
        pBgColorPressed: "#1e1e1e"
        pTextPointSize: wipeLogic.getFontPointSizeM();
        pTextColor: "#ffffff"
        pText: qsTr("    Back");
        pIconSrc: "qrc:/images/menu_back.png"
        onBtnClicked: closeDrawer();
    }

}

