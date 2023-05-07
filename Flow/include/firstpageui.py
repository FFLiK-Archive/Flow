import sys
from PyQt6.QtCore import *
from PyQt6.QtGui import *
from PyQt6.QtWidgets import *

from mainwindowui import *
from firstpageui import *
from filetypeselecter import *



class Ui_Dialog(object):
    def __init__(self, Dialog):
        super().__init__()
        Dialog.resize(300,400)
        self.verticalLayoutWidget = QWidget(Dialog)
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


        self.retranslateUi(Dialog)

        QMetaObject.connectSlotsByName(Dialog)

        
 
    # setupUi
    def retranslateUi(self, Dialog):
        Dialog.setWindowTitle(QCoreApplication.translate("Dialog", u"Dialog", None))
        self.logo.setText(QCoreApplication.translate("Dialog", u"Flow", None))
        self.OpenButton.setText(QCoreApplication.translate("Dialog", u"Open", None))
        self.NewButton.setText(QCoreApplication.translate("Dialog", u"New", None))
    # retranslateUi

    def NewButtonClicked(self):
        
        #Actions to do when the new button is clicked
        print("New Button clicked!")
        MainWindow = QMainWindow()
        window = Ui_ChooseDialog(MainWindow)
        MainWindow.show()
        
        
    def OpenButtonClicked(self):
        #Actions to do when the Open button is clicked
        print("Open Button clicked!")
        window = Ui_ChooseDialog()
        window.show()
    

    
