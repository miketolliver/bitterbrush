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
        id: wipeDeviceColumn
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
                id: wipeDevLeftImg
                anchors.left: parent.left;
                anchors.verticalCenter: wipeDevText.verticalCenter;
                width: height;
                height: Math.min(sourceSize.height, Math.round(spacer.paintedHeight*3.7));
                source: "qrc:/images/ic_nuke.png"
                fillMode: Image.PreserveAspectFit
                smooth: true;
            }

            Text{
                id: wipeDevText
                anchors.left: wipeDevLeftImg.right
                anchors.leftMargin: spacer.paintedHeight;
                anchors.right: parent.right;
                //anchors.margins: 10;
                color: "#7b7b7b"
                text: qsTr("Activating this button will trigger the permanent deletion of all data on this device. <b>This process is not reversible</b>");
                wrapMode: Text.Wrap;
                font.pointSize: wipeLogic.getFontPointSizeM2();
                lineHeight: 1.5;
                lineHeightMode: Text.ProportionalHeight;
            }
        }


        Rectangle{
            anchors.left: parent.left;
            anchors.right: parent.right;
            height: childrenRect.height;

            Image{
                id: cautionImg
                anchors.right: cautionTxt.left;
                anchors.verticalCenter: cautionTxt.verticalCenter;
                anchors.rightMargin: 10;
                width: height;
                height: Math.min(sourceSize.height, Math.round(spacer.paintedHeight*1.75));
                source: "qrc:/images/ic_warning.png"
                fillMode: Image.PreserveAspectFit
                smooth: true;
            }

            Text{
                id: cautionTxt
                anchors.horizontalCenter: parent.horizontalCenter;
                color: "#e91b39"
                text: qsTr("Proceed with caution!");
                font.pointSize: wipeLogic.getFontPointSizeL();
                font.bold: true;
            }
        }


        PlainButton{
            id: wipeBtn
            width: parent.width;
            height: Math.round(cautionTxt.paintedHeight*2.25);
            pBgColor: "#e91b39"
            pBgColorPressed: "#FF0b29"
            pTextPointSize: wipeLogic.getFontPointSizeL();
            pTextColor: "#ffffff"
            pText: qsTr("Wipe This Device");
        }

    }





}

