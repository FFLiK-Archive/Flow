import sys

from PyQt6.QtCore import *
from PyQt6.QtGui import *
from PyQt6.QtWidgets import *
import happyhappyhappy

import mainui

import flow

class conflictDialog(QMainWindow):
    def __init__(self, parent):
        super(conflictDialog, self).__init__()
        #with open(
        #        file="./style.txt", mode="r"
        #) as f:
        #    self.setStyleSheet(f.read())

        self.centralwidget = QWidget()
        self.fuckyeah = happyhappyhappy.happy()

        self.parent:mainui.Ui_MainWindow = parent

    def retranslateUi(self, MainWindow):
        _translate = QCoreApplication.translate
        MainWindow.setWindowTitle(_translate("MainWindow", "MainWindow"))

    def set_change(self, log):
        self.select_data = [0] * len(log)
        self.resize(300, 200)

        self.verticalLayoutWidget = QWidget()
        self.verticalLayoutWidget.setObjectName(u"verticalLayoutWidget")
        self.verticalLayoutWidget.setGeometry(QRect(100, 100, 100, 100))

        self.verticalLayout = QVBoxLayout(self.verticalLayoutWidget)
        self.verticalLayout.setObjectName(u"verticalLayout")
        self.verticalLayout.setContentsMargins(0, 0, 0, 0)

        _translate = QCoreApplication.translate  

        self.label = QLabel(self.centralwidget)
        self.label.setText("Please choose an option to resolve conflicts")
        self.verticalLayout.addWidget(self.label)     

        for i in range(len(log)):
            self.horizontalLayoutWidget = QWidget()

            self.horizontalLayout = QHBoxLayout()
            self.horizontalLayout.setObjectName(str(i))
            self.horizontalLayout.setContentsMargins(0, 0, 0, 0)

            self.label = QLabel(self.centralwidget)
            self.label.setText("File" + str(log[i][0]))
            self.horizontalLayout.addWidget(self.label)

            if log[i][1] == "origin" or log[i][1] == "duplicate":
                self.originButton = QPushButton(self.centralwidget)
                self.originButton.setObjectName(str(i))
                self.originButton.clicked.connect(lambda: self.originButtonClicked())
                self.originButton.setText(_translate("MainWindow", "Original"))
                self.horizontalLayout.addWidget(self.originButton)
            
            if log[i][1] == "target" or log[i][1] == "duplicate":
                self.targetButton = QPushButton(self.centralwidget)
                self.targetButton.setObjectName(str(i))
                self.targetButton.clicked.connect(lambda: self.targetButtonClicked())
                self.targetButton.setText(_translate("MainWindow", "Target"))
                self.horizontalLayout.addWidget(self.targetButton)

            self.NoneButton = QPushButton(self.centralwidget)
            self.NoneButton.setObjectName(str(i))
            self.NoneButton.clicked.connect(lambda: self.NoneButtonClicked())
            self.NoneButton.setText(_translate("MainWindow", "None"))
            self.horizontalLayout.addWidget(self.NoneButton)

            self.verticalLayout.addLayout(self.horizontalLayout)
        
        self.doneButton = QPushButton(self.centralwidget)
        self.doneButton.clicked.connect(self.finalclick)
        self.doneButton.setText(_translate("MainWindow", "Done"))
        self.verticalLayout.addWidget(self.doneButton)

        self.setCentralWidget(self.verticalLayoutWidget)
        self.retranslateUi(self)
        QMetaObject.connectSlotsByName(self)


    def originButtonClicked(self):
        u = self.sender()
        self.select_data[int(u.objectName())] = 1
        print("original button clicked " + u.objectName())

        pass

    def targetButtonClicked(self):
        u = self.sender()
        self.select_data[int(u.objectName())] = 2
        print("target button clicked " + u.objectName())

        pass

    def NoneButtonClicked(self):
        u = self.sender()
        self.select_data[int(u.objectName())] = 0
        print("None button clicked " + u.objectName())
        pass

    def SetID(self, id):
        self.branch_id = id

    def finalclick(self):
        dat = []
        for i in self.select_data:
            dat.append(str(i))
        print(["merge_2", self.branch_id] + dat)
        flow.command(["merge_2", self.branch_id] + dat)
        self.parent.setEnabled(True)
        #self.fuckyeah.show()
        self.hide()


if __name__ == '__main__':
    # Create the QApplication
    app = QApplication(sys.argv)
    window = conflictDialog()
    window.show()

    sys.exit(app.exec())
