import sys
from PyQt6.QtCore import *
from PyQt6.QtGui import *
from PyQt6.QtWidgets import *

from mainwindowui import *
from firstpageui import *
from filetypeselecter import *


class Ui_ChooseDialog(QMainWindow):
    def __init__(self):
        super().__init__()
        self.resize(1168, 728)
        # self.verticalLayoutWidget = QWidget(ChooseDialog)
        self.verticalLayoutWidget.setObjectName(u"verticalLayoutWidget")
        self.verticalLayoutWidget.setGeometry(QRect(470, 280, 218, 80))
        self.verticalLayout = QVBoxLayout(self.verticalLayoutWidget)
        self.verticalLayout.setObjectName(u"verticalLayout")
        self.verticalLayout.setContentsMargins(0, 0, 0, 0)
        self.label = QLabel(self.verticalLayoutWidget)
        self.label.setObjectName(u"label")

        self.verticalLayout.addWidget(self.label)

        self.horizontalLayout = QHBoxLayout()
        self.horizontalLayout.setObjectName(u"horizontalLayout")
        #########
        self.FolderButton = QPushButton(self.verticalLayoutWidget)
        self.FolderButton.setObjectName(u"FolderButton")
        self.FolderButton.clicked.connect(self.FolderButtonClicked)

        self.horizontalLayout.addWidget(self.FolderButton)
        #########
        self.FileButton = QPushButton(self.verticalLayoutWidget)
        self.FileButton.setObjectName(u"FileButton")
        self.FileButton.clicked.connect(self.FileButtonClicked)

        self.horizontalLayout.addWidget(self.FileButton)


        self.verticalLayout.addLayout(self.horizontalLayout)


        self.retranslateUi(ChooseDialog)

        QMetaObject.connectSlotsByName(ChooseDialog)
    # setupUi

    def retranslateUi(self, ChooseDialogue):
        ChooseDialogue.setWindowTitle(QCoreApplication.translate("ChooseDialogue", u"Dialog", None))
        self.label.setText(QCoreApplication.translate("ChooseDialogue", u"Choose the type of your project.", None))
        self.FolderButton.setText(QCoreApplication.translate("ChooseDialogue", u"Folder", None))
        self.FileButton.setText(QCoreApplication.translate("ChooseDialogue", u"File", None))
    # retranslateUi

    def FileButtonClicked(self):
        #Actions to do when the file button is clicked
        print("File Button clicked!")

    def FolderButtonClicked(self):
        #Actions to do when the folder button is clicked
        print("Folder Button clicked!")





