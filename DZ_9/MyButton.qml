import QtQuick 2.0

BorderImage {

    property alias text: _txt.text
    signal clicked
    source: "qrc:///img/but_ready.jpg"
    width: _txt.width + 15
    height: _txt.height + 12
    border{ left: 15; top: 12; right: 15; bottom: 12 }

    Text{
        id:_txt
        color: "black"
        font.pixelSize: 30
        anchors.centerIn: parent
    }

    MouseArea{
        anchors.fill: parent
        onClicked: parent.clicked()
        onPressed: {parent.source = "qrc:/img/but_pressed.jpg"}
        onReleased: {parent.source = "qrc:///img/but_ready.jpg"}
    }

}
