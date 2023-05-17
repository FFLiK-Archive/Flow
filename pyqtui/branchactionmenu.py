import sys

from PyQt6.QtCore import *
from PyQt6.QtGui import *
from PyQt6.QtWidgets import *

import happyhappyhappy
import branchselection
from branchselection import *

import newsubdialog

import mainui

import flow

class branch_menu(QMainWindow):
    def __init__(self, parent):
        super(branch_menu, self).__init__()
        with open(
                file="./style.txt", mode="r"
        ) as f:
            self.setStyleSheet(f.read())

        self.fuckyeah = happyhappyhappy.happy(parent)

        self.parent:mainui.Ui_MainWindow = parent
        self.r = newsubdialog.newsubDialog(self.parent)

        self.bselection = branchselection.branch_selection(self.parent)

        self.centralwidget = QWidget()

        self.resize(300, 400)
        self.verticalLayoutWidget = QWidget()
        self.verticalLayoutWidget.setObjectName(u"verticalLayoutWidget")
        self.verticalLayoutWidget.setGeometry(QRect(100, 100, 100, 100))
        self.verticalLayout = QVBoxLayout(self.verticalLayoutWidget)
        self.verticalLayout.setObjectName(u"verticalLayout")
        self.verticalLayout.setContentsMargins(0, 0, 0, 0)

        # For displaying confirmation message along with user's info.
        self.label = QLabel(self.centralwidget)
        self.label.setText("Select an action")
        self.verticalLayout.addWidget(self.label)

        self.NewSubBranchButton = QPushButton(self.centralwidget)
        self.NewSubBranchButton.clicked.connect(self.NewSubBranchButtonClicked)
        self.verticalLayout.addWidget(self.NewSubBranchButton)

        self.horizontalLayout = QHBoxLayout()
        self.horizontalLayout.setObjectName(u"horizontalLayout")

        self.MergeButton = QPushButton(self.centralwidget)
        self.MergeButton.clicked.connect(self.MergeButtonClicked)
        self.horizontalLayout.addWidget(self.MergeButton)

        self.ReplaceButton = QPushButton(self.centralwidget)
        self.ReplaceButton.clicked.connect(self.ReplaceButtonClicked)
        self.horizontalLayout.addWidget(self.ReplaceButton)

        self.verticalLayout.addLayout(self.horizontalLayout)

        self.DeleteButton = QPushButton(self.centralwidget)
        self.DeleteButton.clicked.connect(self.DeleteButtonClicked)
        self.verticalLayout.addWidget(self.DeleteButton)

        self.RenameButton = QPushButton(self.centralwidget)
        self.RenameButton.clicked.connect(self.RenameButtonClicked)
        self.verticalLayout.addWidget(self.RenameButton)

        self.setCentralWidget(self.verticalLayoutWidget)
        self.retranslateUi(self)
        QMetaObject.connectSlotsByName(self)

    def hideEvent(self, event):
        self.bool = False
        self.parent.setEnabled(True)

    def showEvent(self, event):
        self.parent.setEnabled(False)

    def retranslateUi(self, MainWindow):
        _translate = QCoreApplication.translate
        MainWindow.setWindowTitle(_translate("MainWindow", "MainWindow"))
        self.NewSubBranchButton.setText(_translate("MainWindow", "New Sub Branch"))
        self.MergeButton.setText(_translate("MainWindow", "Merge"))
        self.ReplaceButton.setText(_translate("MainWindow", "Replace"))
        self.DeleteButton.setText(_translate("MainWindow", "Delete"))
        self.RenameButton.setText(_translate("MainWindow", "Rename"))

    def NewSubBranchButtonClicked(self):
        #self.fuckyeah.show()
        self.hide()
        self.r.show()


    def MergeButtonClicked(self):
        if len(flow.branch_list) > 1:
            self.bselection.SetBranch()
            self.bselection.SetCommand("merge")
            self.hide()
            self.bselection.show()

    def ReplaceButtonClicked(self):
        if len(flow.branch_list) > 1:
            self.bselection.SetBranch()
            self.bselection.SetCommand("replace")
            self.hide()
            self.bselection.show()

    def DeleteButtonClicked(self):
        ret = flow.command(["delete_branch"])
        #self.fuckyeah.show()
        self.parent.SetUIData()
        self.hide()

    def RenameButtonClicked(self):
        name = None
        while not name:
            name, done1 = QInputDialog.getText(
            self, 'Input Dialog', 'Enter New Name:')
            if not done1:
                self.hide()
                return

        if done1:
            self.label.setText('Progress Saved Successfully\nName: '+str(name))
            ret = flow.command(["change_name", str(name)])
            
        #print("RenameButtonClicked")
        self.parent.SetUIData()
        self.hide()
        self.fuckyeah.show()

if __name__ == '__main__':
    # Create the QApplication
    app = QApplication(sys.argv)
    window = branch_menu(None)
    window.show()

    sys.exit(app.exec())