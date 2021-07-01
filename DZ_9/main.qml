import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12
import Organizer 1.0

Window {
    width: 1000
    height: 600
    visible: true
    title: qsTr("DZ_9")

    Organizer{
        id:_organizer
    }

    ColumnLayout {

        width: parent.width
        height: parent.height
        anchors.centerIn: parent
        spacing: 1

        TextField{
            id: _name
            Layout.alignment: Qt.AlignCenter
            Layout.preferredWidth: 350
                     Layout.preferredHeight: 50
            Layout.row: 1
            Layout.column: 1
            text: "Название задачи"
        }

        TextField{
            id: _deadline
            Layout.alignment: Qt.AlignCenter
            Layout.preferredWidth: 350
                     Layout.preferredHeight: 50
            Layout.row: 2
            Layout.column: 1
            text: "Дедлайн"
        }

        TextField{
            id: _progress
            Layout.alignment: Qt.AlignCenter
            Layout.preferredWidth: 350
                     Layout.preferredHeight: 50
            Layout.row: 3
            Layout.column: 1
            text: "Текущий прогресс"
        }

        MyButton{
            Layout.alignment: Qt.AlignCenter
            Layout.preferredWidth: 350
            Layout.preferredHeight: 100
            Layout.row: 4
            Layout.column: 1
            text: "Добавить задачу"
            onClicked: _organizer.buttonPress(_name.text, _deadline.text, _progress.text)

        }
    }
}
