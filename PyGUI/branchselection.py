import sys

from PyQt6.QtCore import *
from PyQt6.QtGui import *
from PyQt6.QtWidgets import *
import happyhappyhappy
import conflictdialog

import mainui

import flow

import subprocess

class branch_selection(QMainWindow):
    def __init__(self, parent):
        super(branch_selection, self).__init__()
        with open(
                file="./style.st", mode="r"
        ) as f:
            self.setStyleSheet(f.read())
        self.setWindowIcon(QIcon('logo.png'))
        self.fuckyeah = happyhappyhappy.happy(parent)
        self.cd = conflictdialog.conflictDialog(parent)

        self.parent:mainui.Ui_MainWindow = parent

        self.centralwidget = QWidget()

        self.parent:mainui.Ui_MainWindow = parent

        self.resize(300, 400)
        self.verticalLayoutWidget = QWidget()
        self.verticalLayoutWidget.setObjectName(u"verticalLayoutWidget")
        self.verticalLayoutWidget.setGeometry(QRect(100, 100, 100, 100))
        self.verticalLayout = QVBoxLayout(self.verticalLayoutWidget)
        self.verticalLayout.setObjectName(u"verticalLayout")
        self.verticalLayout.setContentsMargins(0, 0, 0, 0)

        # For displaying confirmation message along with user's info.
        self.label = QLabel(self.centralwidget)
        self.label.setText("Select a branch")
        self.verticalLayout.addWidget(self.label)

        self.BranchList = QListWidget(self.centralwidget)
        self.BranchList.setObjectName(u"BranchList")
        self.BranchList.itemClicked.connect(self.BranchListClicked)

        self.verticalLayout.addWidget(self.BranchList)

        self.cmd = ""

        self.cur_branch = []

        self.setCentralWidget(self.verticalLayoutWidget)
        self.retranslateUi(self)
        QMetaObject.connectSlotsByName(self)

    def hideEvent(self, event):
        self.bool = False
        self.parent.setEnabled(True)

    def showEvent(self, event):
        self.parent.setEnabled(False)

    def SetBranch(self):
        self.BranchList.clear()
        self.cur_branch.clear()
        for i in range(len(flow.branch_list)):
            if i != flow.activated_branch:
                self.cur_branch.append(flow.branch_list[i])
                self.BranchList.addItem(flow.branch_list[i][flow.BRANCH_NAME])

    def SetCommand(self, cmd):
        self.cmd = cmd

    def retranslateUi(self, MainWindow):
        _translate = QCoreApplication.translate
        MainWindow.setWindowTitle(_translate("MainWindow", "MainWindow"))

    def BranchListClicked(self,item):
        ###########################
        ###########################
        # ADD ADDITIONAL CODE HERE!#
        ###########################
        ###########################
        print(item.text())
        if self.cmd == "replace":
            flow.command(["replace", self.cur_branch[self.BranchList.currentRow()][flow.BRANCH_ID]])
            self.parent.setEnabled(True)
            self.hide()
        elif self.cmd == "merge":
            change_log, ret = flow.command(["merge_1", self.cur_branch[self.BranchList.currentRow()][flow.BRANCH_ID]], 2)
            self.cd.set_change(change_log)
            self.cd.SetID(self.cur_branch[self.BranchList.currentRow()][flow.BRANCH_ID])
            self.hide()
            self.cd.show()

if __name__ == '__main__':
    # Create the QApplication
    app = QApplication(sys.argv)
    window = branch_selection(None)
    window.show()

    sys.exit(app.exec())