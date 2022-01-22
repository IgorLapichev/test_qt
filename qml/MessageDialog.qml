import QtQuick 2.9
import QtQuick.Controls 2.2
import QtQuick.Window 2.2


Dialog {
    parent: ApplicationWindow.overlay

    x: (parent.width - width) / 2
    y: (parent.height - height) / 2

    focus: true
    modal: true

    title: qsTr("Error!")
    text: qsTr("Select correct folders!")

    property alias text: messageText.text

    Label {
        id: messageText

        verticalAlignment: Text.AlignVCenter
        horizontalAlignment: Text.AlignHCenter

        anchors.fill: parent
    }

    standardButtons: Dialog.Ok
}
