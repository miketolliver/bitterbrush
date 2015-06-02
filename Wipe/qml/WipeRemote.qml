import QtQuick 1.1

Rectangle {
    width: 100
    height: 62
    color: "white"

    property int pColSpacing: Math.round(height*0.125)

    Text{
        id: spacer
        font.pointSize: wipeLogic.getFontPointSizeM();
        text: "T"
        visible: false;
    }

    Column{
        id: wipeRemoteColumn
        spacing: pColSpacing; // Math.round(3*wipeLogic.getFontPointSizeM2());
        anchors.top: parent.top;
        anchors.left: parent.left;
        anchors.right: parent.right;
        anchors.margins: Math.round(1.25*spacer.paintedHeight);

        Rectangle{
            anchors.left: parent.left;
            anchors.right: parent.right;
            height: childrenRect.height;

            Image{
                id: wipeRemoteLeftImg
                anchors.left: parent.left;
                anchors.verticalCenter: wipeRemoteText.verticalCenter;
                width: height;
                height: Math.min(sourceSize.height, Math.round(spacer.paintedHeight*3.7));
                source: "qrc:/images/ic_nuke.png"
                fillMode: Image.PreserveAspectFit
                smooth: true;
            }

            Text{
                id: wipeRemoteText
                anchors.left: wipeRemoteLeftImg.right
                anchors.leftMargin: spacer.paintedHeight;
                anchors.right: parent.right;
                //anchors.margins: 10;
                color: "#7b7b7b"
                text: qsTr("Enter the email and duress password associated with the device you wish to remotely wipe. <b>This process is not reversible</b>");
                wrapMode: Text.Wrap;
                font.pointSize: wipeLogic.getFontPointSizeM2();
                lineHeight: 1.5;
                lineHeightMode: Text.ProportionalHeight;
            }
        }


        PlainButton{
            id: wipeRemoteBtn
            width: parent.width;
            height: Math.round(spacer.paintedHeight*3.25);
            pBgColor: "#e91b39"
            pBgColorPressed: "#FF0b29"
            pTextPointSize: wipeLogic.getFontPointSizeL();
            pTextColor: "#ffffff"
            pText: qsTr("Wipe Remote Device");
        }


    }





}

