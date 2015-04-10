import QtQuick 1.1

Rectangle {
    width: 360
    height: 360
    Text {
        id: headerTxt
        text: qsTr("Click anywhere to start")
        anchors.centerIn: parent
    }
    MouseArea {
        anchors.fill: parent
        onClicked: {
            headerTxt.text = "running data i/o tests..."
            console.log( "Starting bench work" );
            benchData.doWork();
        }
    }

    Connections{
        target: benchData

        onWorkUpdated:
        {
            console.log( "Work updated signal." );
            headerTxt.text = "work updated."
        }
    }

}
