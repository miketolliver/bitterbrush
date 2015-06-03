import QtQuick 1.1

Rectangle {
    id: settingsRoot;
    width: 100
    height: 300
    color: "#ffffff"

    signal closeSettings();


    Rectangle{
        id: settingsHeader;
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.top: parent.top;
        height: closeBtn.height;

        PlainButton{
            id: closeBtn
            pTextColor: "#00a8dd"
            pText: qsTr("CLOSE");
            pBgColor: "transparent"
            pBgColorPressed:  "#2200a8dd"
            pTextPointSize: wipeLogic.getFontPointSizeM2();
            pHeightMult: 2.5;
            onBtnClicked: closeSettings();
        }

        Rectangle{
            id:vertLine1
            anchors.left: closeBtn.right;
            anchors.bottom: parent.bottom
            anchors.top: parent.top;
            anchors.topMargin: Math.round(parent.height*0.12);
            anchors.bottomMargin: anchors.topMargin;
            width: 1;
            color: "#d2d2d2"
        }
        Text{
            id: headerTxt
            anchors.left: vertLine1.right
            anchors.leftMargin: paintedHeight;
            anchors.right: parent.right;
            //anchors.verticalCenter: parent.verticalCenter;
            anchors.top: parent.top;
            anchors.bottom: parent.bottom;

            color: "#333333"
            text: qsTr("Remote Settings");
            font.pointSize: wipeLogic.getFontPointSizeM2();
            horizontalAlignment: Text.AlignLeft
            verticalAlignment: Text.AlignVCenter
            font.bold: true;
        }
    }

    Rectangle{
        id:horzLine1
        anchors.left: settingsHeader.left
        anchors.right: settingsHeader.right;
        anchors.top: settingsHeader.bottom;
        height: 1;
        color: "#00a8dd"
    }

    Column{
        id: settingsCol
        anchors.left: parent.left
        anchors.right: parent.right;
        anchors.top: horzLine1.bottom;
        anchors.margins: Math.round(headerTxt.paintedHeight*1.0);
        spacing: Math.round(headerTxt.paintedHeight * 1.5);

        Text {
            id: settingsTxt
            width: parent.width;
            text: qsTr("Please enter the email and duress password to "+
                        "be used if you need to remotely wipe this "+
                        "device in the event it becomes compromised.");
            color: "#3b3b3b"
            wrapMode: Text.Wrap;
            font.pointSize: wipeLogic.getFontPointSizeM();
            lineHeight: 1.25;
            lineHeightMode: Text.ProportionalHeight;

        }

        MyTextField{
            id: oldPwInput
            width: parent.width;
            pIsPw: true;
            pPlaceHolderText: qsTr("Old password (leave blank if not set)");
        }


        MyTextField{
            id: newPwInput
            width: parent.width;
            pIsPw: true;
            pPlaceHolderText: qsTr("New duress password");
        }

        MyTextField{
            id: confirmPwInput
            width: parent.width;
            pIsPw: true;
            pPlaceHolderText: qsTr("Confirm password");
        }

        PlainButton{
            id: enterBtn;
            pBgColor: "#00a8dd"
            pBgColorPressed: "#00b8FF"
            pText: qsTr("     Enter     ");
            pTextColor: "#FFFFFF"
            pTextPointSize: wipeLogic.getFontPointSizeL();
            pHeightMult: 2.0;
        }

    }




}

