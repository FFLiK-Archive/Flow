import sys

from PyQt6.QtCore import *
from PyQt6.QtGui import *
from PyQt6.QtWidgets import *
import happyhappyhappy

import mainui


class history_selection(QMainWindow):
    def __init__(self, parent):
        super(history_selection, self).__init__()
        with open(
                file="./style.st", mode="r"
        ) as f:
            self.setStyleSheet(f.read())

        self.fuckyeah = happyhappyhappy.happy(parent)
        self.setWindowIcon(QIcon('logo.png'))
        
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
        self.label.setText("Select a history")
        self.verticalLayout.addWidget(self.label)

        self.historyList = QListWidget(self.centralwidget)
        self.historyList.setObjectName(u"historyList")
        self.historyList.itemClicked.connect(self.historyListClicked)

        self.verticalLayout.addWidget(self.historyList)

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
        MainWindow.setWindowTitle(_translate("MainWindow", "Flow"))

    def historyListClicked(self,item):
        ###########################
        ###########################
        # ADD ADDITIONAL CODE HERE!#
        ###########################
        ###########################
        print(item.text())
        self.hide()
        self.fuckyeah.show()

if __name__ == '__main__':
    # Create the QApplication
    app = QApplication(sys.argv)
    window = history_selection()
    window.show()

    sys.exit(app.exec())