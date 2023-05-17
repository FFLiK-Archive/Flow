import sys
from PyQt6.QtCore import *
from PyQt6.QtGui import *
from PyQt6.QtWidgets import *

import branchselection
from branchselection import *

import mainui

class happy(QMainWindow):
    def __init__(self, parent):
        super(happy, self).__init__()
        with open(
                file="./style.txt", mode="r"
        ) as f:
            self.setStyleSheet(f.read())

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
        self.label.setText("Successful!")
        self.verticalLayout.addWidget(self.label)

        self.doneButton = QPushButton(self.centralwidget)
        self.doneButton.clicked.connect(self.Clicked)
        self.verticalLayout.addWidget(self.doneButton)


        self.setCentralWidget(self.verticalLayoutWidget)
        self.retranslateUi(self)
        QMetaObject.connectSlotsByName(self)

    def retranslateUi(self, MainWindow):
        _translate = QCoreApplication.translate
        MainWindow.setWindowTitle(_translate("MainWindow", "Flow"))
        self.doneButton.setText(_translate("MainWindow", "Done"))

    def Clicked(self):
        print("happydonebuttonClicked")
        self.hide()

    def hideEvent(self, event):
        self.bool = False
        self.parent.setEnabled(True)

    def showEvent(self, event):
        self.parent.setEnabled(False)

if __name__ == '__main__':
    # Create the QApplication
    app = QApplication(sys.argv)
    window = happy(None)
    window.show()

    sys.exit(app.exec())