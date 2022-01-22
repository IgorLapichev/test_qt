import QtQuick 2.9
import QtQuick.Controls 2.2
import QtQuick.Window 2.2
import Qt.labs.folderlistmodel 2.2


Rectangle {
    border.color: 'black'

    property string folderPathName: qsTr("");
    property int itemHeight: 20

    Item {
        x: 0
        y: 0
        width: parent.width
        height: itemHeight

        Text {
            anchors.fill: parent
            font.bold: true
            text: qsTr("...")
        }

        MouseArea {
            anchors.fill: parent
            onDoubleClicked: {
                folderListModel.folder = folderListModel.parentFolder
            }
        }
    }

    ListView {
        id: listView

        y: itemHeight
        width: parent.width
        height: parent.height - 25
        clip: true

        ScrollBar.vertical: ScrollBar {
            policy: ScrollBar.AlwaysOn
            active: ScrollBar.AlwaysOn
        }

        model: FolderListModel {
            id: folderListModel
            showDirsFirst: true
        }

        property string currentPath: qsTr("")

        delegate: Item {
            width: parent.width
            height: itemHeight

            Text {
                id: itemText

                anchors.fill: parent
                anchors.leftMargin: 10
                anchors.verticalCenter: itemText.verticalCenter
                text: fileName
                font.pointSize: 10
            }

            MouseArea {
                anchors.fill: parent
                onClicked: {
                    listView.currentIndex = index
                    if (fileIsDir) {
                        folderPathName = fileURL
                    }
                    else {
                        folderPathName = qsTr("")
                    }
                }
                onDoubleClicked: {
                    if (fileIsDir) {
                        folderListModel.folder = fileURL
                    }
                }
            }

            Component.onCompleted: {
                if (fileIsDir) {
                    itemText.font.bold = true
                }
            }
        }

        highlight: Rectangle {
            color: 'cyan'
        }
    }

    function getCurrentPath() {
        return folderPathName
    }
}
