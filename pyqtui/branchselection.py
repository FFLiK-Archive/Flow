import sys

from PyQt6.QtCore import *
from PyQt6.QtGui import *
from PyQt6.QtWidgets import *
import happyhappyhappy
import conflictdialog

import mainui

import flow

class branch_selection(QMainWindow):
    def __init__(self, parent):
        super(branch_selection, self).__init__()

        self.fuckyeah = happyhappyhappy.happy()
        self.cd = conflictdialog.conflictDialog()

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
        self.cd.show()
        if self.cmd == "replace":
            flow.command(["replace", self.cur_branch[self.BranchList.currentRow()][flow.BRANCH_ID]])
            self.parent.setEnabled(True)
        elif self.cmd == "merge":
            pass
        #self.fuckyeah.show()
        self.hide()

if __name__ == '__main__':
    # Create the QApplication
    app = QApplication(sys.argv)
    window = branch_selection()
    window.show()

    sys.exit(app.exec())