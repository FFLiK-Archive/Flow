import sys
from PyQt6.QtCore import *
from PyQt6.QtGui import *
from PyQt6.QtWidgets import *

import mainui
import filetypeselecter

import subprocess

class Ui_Dialog(QMainWindow):
    def __init__(self):
        super(Ui_Dialog, self).__init__()

        self.second_window = filetypeselecter.Ui_ChooseDialog()

        self.resize(300, 400)
        self.verticalLayoutWidget = QWidget()
        self.verticalLayoutWidget.setObjectName(u"verticalLayoutWidget")
        self.verticalLayoutWidget.setGeometry(QRect(100, 100, 100, 100))
        self.verticalLayout = QVBoxLayout(self.verticalLayoutWidget)
        self.verticalLayout.setObjectName(u"verticalLayout")
        self.verticalLayout.setContentsMargins(0, 0, 0, 0)
        self.logo = QLabel(self.verticalLayoutWidget)
        self.logo.setObjectName(u"logo")

        self.verticalLayout.addWidget(self.logo)

        self.horizontalLayout = QHBoxLayout()
        self.horizontalLayout.setObjectName(u"horizontalLayout")
        ##############
        self.OpenButton = QPushButton(self.verticalLayoutWidget)
        self.OpenButton.setObjectName(u"OpenButton")
        self.OpenButton.clicked.connect(self.OpenButtonClicked)

        self.horizontalLayout.addWidget(self.OpenButton)
        #############
        self.NewButton = QPushButton(self.verticalLayoutWidget)
        self.NewButton.setObjectName(u"NewButton")
        self.NewButton.clicked.connect(self.NewButtonClicked)

        self.horizontalLayout.addWidget(self.NewButton)

        self.verticalLayout.addLayout(self.horizontalLayout)
        self.setCentralWidget(self.verticalLayoutWidget)
        self.retranslateUi(self)

        QMetaObject.connectSlotsByName(self)

    # setupUi
    def retranslateUi(self, Dialog):
        Dialog.setWindowTitle(QCoreApplication.translate("Dialog", u"Dialog", None))
        self.logo.setText(QCoreApplication.translate("Dialog", u"Flow", None))
        self.OpenButton.setText(QCoreApplication.translate("Dialog", u"Open", None))
        self.NewButton.setText(QCoreApplication.translate("Dialog", u"New", None))

    # retranslateUi

    def NewButtonClicked(self):
        # Actions to do when the new button is clicked
        ###########################
        ###########################
        print("New Button clicked!")
        self.second_window.show()
        self.hide()

    def OpenButtonClicked(self):
        # Actions to do when the Open button is clicked
        ###########################
        proc = subprocess.Popen(['Flow', 'open'],stdout=subprocess.PIPE, stdin=subprocess.PIPE)
        proc.wait()
        ###########################
        print("Open Button clicked!")
        if proc.returncode == 0:
            self.second_window.third_window.SetUIData()
            self.second_window.third_window.show()
            self.hide()

