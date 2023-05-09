import sys

from PyQt6.QtCore import *
from PyQt6.QtGui import *
from PyQt6.QtWidgets import *
import happyhappyhappy
import conflictdialog


class branch_selection(QMainWindow):
    def __init__(self):
        super(branch_selection, self).__init__()

        self.fuckyeah = happyhappyhappy.happy()
        self.cd = conflictdialog.conflictDialog()

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
        self.label.setText("Select a branch")
        self.verticalLayout.addWidget(self.label)

        self.BranchList = QListWidget(self.centralwidget)
        self.BranchList.setObjectName(u"BranchList")
        self.BranchList.addItem("Branch1")
        self.BranchList.addItem("branch2")
        self.BranchList.addItem("branch3")
        self.BranchList.itemClicked.connect(self.BranchListClicked)

        self.verticalLayout.addWidget(self.BranchList)



        self.setCentralWidget(self.verticalLayoutWidget)
        self.retranslateUi(self)
        QMetaObject.connectSlotsByName(self)


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
        self.fuckyeah.show()
        self.hide()

if __name__ == '__main__':
    # Create the QApplication
    app = QApplication(sys.argv)
    window = branch_selection()
    window.show()

    sys.exit(app.exec())