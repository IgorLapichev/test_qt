import TestApp 1.0

import QtQuick 2.9
import QtQuick.Controls 2.2
import QtQuick.Window 2.2
import Qt.labs.folderlistmodel 2.2

Window {
    visible: true
    width: 800
    height: 600
    title: qsTr("Comparator")

    Item {
        id: mainView
        anchors.fill: parent

        property int gap:    10
        property int dblgap: 20

        CustomTreeView {
            id: leftTreeView

            x: mainView.gap
            y: mainView.gap
            width: parent.width / 2 - mainView.gap
            height: parent.height / 2 - mainView.dblgap
        }

        CustomTreeView {
            id: rightTreeView

            x: parent.width / 2 + mainView.gap
            y: mainView.gap
            width: parent.width / 2 - mainView.dblgap
            height: parent.height / 2 - mainView.dblgap
        }

        Button {
            id: checkButton

            anchors.right: rightTreeView.right
            anchors.top: rightTreeView.bottom
            anchors.topMargin: 20

            width: 100
            height: 30

            text: qsTr("Check folders")

            onClicked: {
                var leftPath = leftTreeView.getCurrentPath()
                var rightPath = rightTreeView.getCurrentPath()

                if (leftPath === "" || rightPath === "")
                {
                    centeredDialog.visible = true
                    return
                }

                testManager.compareFolders(leftPath.substring(8), rightPath.substring(8));
            }
        }

        ComboBox {

            anchors.left: leftTreeView.left
            anchors.top: leftTreeView.bottom
            anchors.topMargin: 20

            width: 150
            height: 30

            textRole: "key"
            model: ListModel {
                ListElement { key: qsTr("Binary check"); value: 1 }
                ListElement { key: qsTr("Hash check"); value: 2 }
            }

            onCurrentIndexChanged: {
                testManager.changeSelectionMethod(currentIndex);
            }
        }

        Rectangle {
            id: resultsView

            border.color: 'black'

            anchors.top: checkButton.bottom
            anchors.topMargin: 20

            anchors.left: leftTreeView.left
            anchors.right: rightTreeView.right
            anchors.bottom: mainView.bottom
            anchors.bottomMargin: 20


            ListView {
                id: resultsList
                anchors.fill: parent
                clip: true

                model: ListModel {
                    id: listModel
                }

                ScrollBar.vertical: ScrollBar {
                    policy: ScrollBar.AlwaysOn
                    active: ScrollBar.AlwaysOn
                }

                delegate: Item {
                    id: item

                    width: parent.width
                    height: 20

                    Text {
                        anchors.fill: parent
                        anchors.leftMargin: 10
                        anchors.verticalCenter: itemText.verticalCenter

                        text: idshnik
                    }
                }

                Connections {
                    target: testManager

                    onResultModelChanged: {
                        var folders = testManager.resultModel;

                        listModel.clear()
                        listModel.append({idshnik: "Results..."})
                        for (var i = 0; i < folders.length; i+=2)
                        {
                            listModel.append({idshnik: folders[i]})
                            listModel.append({idshnik: folders[i + 1]})
                            listModel.append({idshnik: "..."})
                        }
                    }
                }
            }
        }

        MessageDialog {
            id: centeredDialog
        }
    }
}

