import sys

from PyQt6.QtCore import *
from PyQt6.QtGui import *
from PyQt6.QtWidgets import *
import happyhappyhappy

from historyselection import *
import historyselection

import mainui
import flow

class history_menu(QMainWindow):
    def __init__(self, parent):
        super(history_menu, self).__init__()

        self.fuckyeah = happyhappyhappy.happy(parent)

        self.parent:mainui.Ui_MainWindow = parent

        self.hselection = historyselection.history_selection(parent)

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
        self.label.setText("Select an action")
        self.verticalLayout.addWidget(self.label)

        self.RevertButton = QPushButton(self.centralwidget)
        self.RevertButton.clicked.connect(self.RevertButtonClicked)
        self.verticalLayout.addWidget(self.RevertButton)

        self.DeleteButton = QPushButton(self.centralwidget)
        self.DeleteButton.clicked.connect(self.DeleteButtonClicked)
        self.verticalLayout.addWidget(self.DeleteButton)

        self.setCentralWidget(self.verticalLayoutWidget)
        self.retranslateUi(self)
        QMetaObject.connectSlotsByName(self)
        self.index = -1

    def hideEvent(self, event):
        self.bool = False
        self.parent.setEnabled(True)

    def showEvent(self, event):
        self.parent.setEnabled(False)

    def SetIndex(self, index):
        self.index = index

    def retranslateUi(self, MainWindow):
        _translate = QCoreApplication.translate
        MainWindow.setWindowTitle(_translate("MainWindow", "MainWindow"))
        self.RevertButton.setText(_translate("MainWindow", "Revert"))
        self.DeleteButton.setText(_translate("MainWindow", "Delete"))

    def RevertButtonClicked(self):
        if self.index != -1:
            flow.command(["revert", str(self.index)])
        self.parent.SetUIData()
        self.hide()
        self.fuckyeah.show()

    def DeleteButtonClicked(self):
        if self.index != -1:
            flow.command(["delete", str(self.index)])
        self.parent.SetUIData()
        self.hide()
        self.fuckyeah.show()

if __name__ == '__main__':
    # Create the QApplication
    app = QApplication(sys.argv)
    window = history_menu(None)
    window.show()

    sys.exit(app.exec())