import QtQuick 1.1

Rectangle {
    width: 100
    height: 62
    color: "white"

    Column{
        id: wipeDeviceColumn
        spacing: 10;
        anchors.top: parent.top;
        anchors.left: parent.left;
        anchors.right: parent.right;

        Rectangle{
            anchors.left: parent.left;
            anchors.right: parent.right;
            height: childrenRect.height;

            Image{
                id: wipeDevLeftImg
                anchors.left: parent.left;
                source: "qrc:/images/ic_nuke.png"
            }

            Text{
                id: wipeDevText
                anchors.left: wipeDevLeftImg.right
                anchors.right: parent.right;
                anchors.margins: 10;
                color: "#7b7b7b"
                text: "Activating this button will trigger the permanent deletion of all data on this device. ";
                wrapMode: Text.Wrap;
            }
        }

        Text{
            id: cautionTxt
            color: "red"
            text: "Proceed with caution!";
        }


    }





}

