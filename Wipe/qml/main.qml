import QtQuick 1.1

Rectangle {
    id: mainRoot;
    width: 420
    height: 420

    property bool pIsDrawerOpen: false;
    property int pWipeOptionState: 1;
    property bool pShowSettings: true; //false;



    PlainButton{
        id: wipeDeviceBtn
        anchors.left: parent.left
        anchors.top: parent.top;
        anchors.right: parent.horizontalCenter;

        pBgColor: pWipeOptionState===1 ? "#282828" : "#FFFFFF"
        pTextColor: pWipeOptionState===1 ? "#FFFFFF" : "#282828"
        pText: "WIPE DEVICE";

        onBtnClicked: {
            pWipeOptionState = 1;
        }
    }
    PlainButton{
        id: wipeRemoteBtn
        anchors.left: wipeDeviceBtn.right
        anchors.top: parent.top;
        anchors.right: parent.right;

        pBgColor: pWipeOptionState===2 ? "#282828" : "#FFFFFF"
        pTextColor: pWipeOptionState===2 ? "#FFFFFF" : "#282828"
        pText: "REMOTE WIPE"

        onBtnClicked: {
            pWipeOptionState = 2;
        }
    }
    Rectangle{
        id: line1
        anchors.left: parent.left
        anchors.right: parent.right;
        anchors.top: wipeDeviceBtn.bottom;
        height: 2;
        color: "#282828";
    }


    WipeDevice{
        id: wipeDevice
        anchors.top: line1.bottom;
        anchors.bottom: footerLine.top
        anchors.left: parent.left;
        width: parent.width;
        enabled: pWipeOptionState===1;
    }
    WipeRemote{
        id: wipeRemote
        anchors.top: line1.bottom;
        anchors.bottom: footerLine.top
        anchors.left: wipeDevice.right;
        width: parent.width;
        enabled: pWipeOptionState===2;
    }

    Rectangle{
        id: footerLine
        anchors.left: parent.left;
        anchors.right: parent.right;
        anchors.bottom: showDrawerBtn.top;
        height: 1
        color: "#d0d0d0"
    }

    PlainIconButton {
        id: showDrawerBtn
        anchors.right: parent.right;
        anchors.bottom: parent.bottom;
        height: wipeDeviceBtn.height;
        width: Math.round(height*0.8);
        pIconSrc: "qrc:/images/ic_overflow_action.png"
        onBtnClicked: {
            pIsDrawerOpen = true;
        }
    }


    RemoteSettings{
        id: settings
        anchors.fill: parent;
        visible: opacity > 0.05;
        enabled: visible;
        opacity: 0.0;

        onCloseSettings: pShowSettings = false;

        states: [
            State {
                when: pShowSettings
                PropertyChanges {
                    target: settings
                    opacity: 1.0
                }
            }
        ]
        transitions:
        [
            Transition
            {
                PropertyAnimation
                {
                    properties: "opacity";
                    duration: 200;
                    easing.type: Easing.OutCurve
                }
            }
        ]
    }


    states: [
        State {
            when: pWipeOptionState===2
            PropertyChanges {
                target: wipeDevice
                anchors.leftMargin: -wipeDevice.width;
            }
        }
    ]
    transitions:
    [
        Transition
        {
            PropertyAnimation
            {
                properties: "anchors.leftMargin,opacity";
                duration: 150;
                easing.type: Easing.OutCubic
            }
        }
    ]

    Rectangle{
        id: drawerHandler
        anchors.fill: parent;
        enabled: pIsDrawerOpen;
        color: "#121212"
        opacity: 0
        visible: opacity > 0.0

        MouseArea{
            id: drawerHandlerMA
            anchors.fill: parent;
            enabled: pIsDrawerOpen;
            onClicked: {
                pIsDrawerOpen = false;
            }
        }
    }

    Drawer{
        id: drawer
        anchors.right: parent.right
        anchors.top: parent.top;
        anchors.bottom: parent.bottom;
        anchors.rightMargin: -width
        enabled: pIsDrawerOpen;

        onCloseDrawer: {
            pIsDrawerOpen = false;
        }
        onOpenSettings: {
            pIsDrawerOpen = false;
            pShowSettings = true;
        }

        states: [
            State {
                when: pIsDrawerOpen
                PropertyChanges {
                    target: drawer
                    anchors.rightMargin: 0;
                }
                PropertyChanges {
                    target: drawerHandler
                    opacity: 0.5;
                }
            }
        ]
        transitions:
        [
            Transition
            {
                PropertyAnimation
                {
                    properties: "anchors.rightMargin,opacity";
                    duration: 300;
                    easing.type: Easing.OutCubic
                }
            }
        ]

    }

}
