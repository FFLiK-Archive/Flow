import sys

from PyQt6.QtCore import *
from PyQt6.QtGui import *
from PyQt6.QtWidgets import *

import mainui
import flow

class newsubDialog(QMainWindow):
    def __init__(self, parent):
        super(newsubDialog, self).__init__()
        #with open(
        #        file="./style.txt", mode="r"
        #) as f:
        #    self.setStyleSheet(f.read())

        self.centralwidget = QWidget()

        self.parent:mainui.Ui_MainWindow = parent

        self.bool = False
        self.resize(300, 200)
        self.verticalLayoutWidget = QWidget()
        self.verticalLayoutWidget.setObjectName(u"verticalLayoutWidget")
        self.verticalLayoutWidget.setGeometry(QRect(100, 100, 100, 100))

        self.verticalLayout = QVBoxLayout(self.verticalLayoutWidget)
        self.verticalLayout.setObjectName(u"verticalLayout")
        self.verticalLayout.setContentsMargins(0, 0, 0, 0)

        # For displaying confirmation message along with user's info.
        self.label = QLabel(self.centralwidget)

        # Keeping the text of label empty initially.
        self.label.setText("Please enter a name for the branch.")
        self.verticalLayout.addWidget(self.label)

        self.pushButton = QPushButton(self.centralwidget)
        self.pushButton.clicked.connect(self.takeinputs)
        self.verticalLayout.addWidget(self.pushButton)


        self.name = ""

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
        self.pushButton.setText(_translate("MainWindow", "Proceed"))
        self.bool = False

    def takeinputs(self):
        ###########################
        ###########################
        # ADD ADDITIONAL CODE HERE!#
        ###########################
        ###########################
        # summary, description stores as str
        _translate = QCoreApplication.translate

        if self.bool:
            flow.command(["create_sub_branch", self.name])
            self.parent.SetUIData()
            self.hide()
            self.retranslateUi(self)

        else:
            name = None
            while not name:
                name, done1 = QInputDialog.getText(
                self, 'Input Dialog', 'Enter New Name:')
                if not done1:
                    self.hide()
                    self.retranslateUi(self)
                    return

            self.bool = True
            self.pushButton.setText(_translate("MainWindow", "Done"))
            if done1:
                self.label.setText('New Branch Added Successfully\nName: '
                                   + str(name))
            self.name = str(name)
                





