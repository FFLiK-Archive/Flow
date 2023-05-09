import sys

from PyQt6.QtCore import *
from PyQt6.QtGui import *
from PyQt6.QtWidgets import *
import happyhappyhappy


class conflictDialog(QMainWindow):
    def __init__(self):
        super(conflictDialog, self).__init__()
        with open(
                file="./style.txt", mode="r"
        ) as f:
            self.setStyleSheet(f.read())
        self.centralwidget = QWidget()
        self.fuckyeah = happyhappyhappy.happy()

        self.scroll = QScrollArea()  # Scroll Area which contains the widgets, set as the centralWidget

        self.resize(350, 400)
        self.verticalLayoutWidget = QWidget()
        self.verticalLayoutWidget.setObjectName(u"verticalLayoutWidget")
        self.verticalLayout = QVBoxLayout(self.verticalLayoutWidget)
        self.verticalLayout.setObjectName(u"verticalLayout")
        self.verticalLayout.setContentsMargins(0, 0, 0, 0)

        self.verticalLayoutWidget1 = QWidget()
        self.verticalLayoutWidget1.setObjectName(u"verticalLayoutWidget1")
        self.verticalLayout1 = QVBoxLayout(self.verticalLayoutWidget1)
        self.verticalLayout1.setObjectName(u"verticalLayout1")
        self.verticalLayout1.setContentsMargins(0, 0, 0, 0)

        self.label = QLabel(self.centralwidget)
        self.label.setText("Please choose an option to resolve conflicts")
        self.verticalLayout.addWidget(self.label)

        _translate = QCoreApplication.translate

        self.L = [ 'rge', 'wergweg','wregwrg',1,2,3,4,34]
        for i in range(len(self.L)):
            self.horizontalLayoutWidget = QWidget()

            self.horizontalLayout = QHBoxLayout()
            self.horizontalLayout.setObjectName(u"horizontalLayout"+ str(i))
            self.horizontalLayout.setContentsMargins(0, 0, 0, 0)

            self.label = QLabel(self.centralwidget)
            self.label.setText("File" + str(self.L[i]))
            self.horizontalLayout.addWidget(self.label)

            self.originButton = QPushButton(self.centralwidget)
            self.originButton.setObjectName(u"originButton" + str(i))
            self.originButton.clicked.connect(lambda: self.originButtonClicked())
            self.originButton.setText(_translate("MainWindow", "Original"))
            self.horizontalLayout.addWidget(self.originButton)

            self.targetButton = QPushButton(self.centralwidget)
            self.targetButton.setObjectName(u"targetButton" + str(i))
            self.targetButton.clicked.connect(lambda: self.targetButtonClicked())
            self.targetButton.setText(_translate("MainWindow", "Target"))
            self.horizontalLayout.addWidget(self.targetButton)

            self.NoneButton = QPushButton(self.centralwidget)
            self.NoneButton.setObjectName(u"NoneButton" + str(i))
            self.NoneButton.clicked.connect(lambda: self.NoneButtonClicked())
            self.NoneButton.setText(_translate("MainWindow", "None"))
            self.horizontalLayout.addWidget(self.NoneButton)

            self.verticalLayout1.addLayout(self.horizontalLayout)

        self.alpha = QWidget()
        self.alpha.setLayout(self.verticalLayout1)
        self.scroll = QScrollArea()
        self.scroll.setWidget(self.alpha)
        self.verticalLayout.addWidget(self.scroll)

        self.doneButton = QPushButton(self.centralwidget)
        self.doneButton.clicked.connect(self.finalclick)
        self.doneButton.setText(_translate("MainWindow", "Done"))
        self.verticalLayout.addWidget(self.doneButton)

        self.setCentralWidget(self.verticalLayoutWidget)
        self.retranslateUi(self)
        QMetaObject.connectSlotsByName(self)

    def retranslateUi(self, MainWindow):
        _translate = QCoreApplication.translate
        MainWindow.setWindowTitle(_translate("MainWindow", "Flow"))




    def originButtonClicked(self):

        u = self.sender()
        print("original button clicked " + u.objectName())

        pass

    def targetButtonClicked(self):
        u = self.sender()
        print("target button clicked " + u.objectName())

        pass

    def NoneButtonClicked(self):
        u = self.sender()
        print("None button clicked " + u.objectName())


        pass

    def finalclick(self):
        self.fuckyeah.show()
        self.hide()


if __name__ == '__main__':
    # Create the QApplication
    app = QApplication(sys.argv)
    window = conflictDialog()
    window.show()

    sys.exit(app.exec())
