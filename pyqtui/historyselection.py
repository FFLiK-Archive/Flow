import sys

from PyQt6.QtCore import *
from PyQt6.QtGui import *
from PyQt6.QtWidgets import *
import happyhappyhappy


class history_selection(QMainWindow):
    def __init__(self):
        super(history_selection, self).__init__()

        self.fuckyeah = happyhappyhappy.happy()

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
        self.label.setText("Select a history")
        self.verticalLayout.addWidget(self.label)

        self.historyList = QListWidget(self.centralwidget)
        self.historyList.setObjectName(u"historyList")
        self.historyList.addItem("history1")
        self.historyList.addItem("history2")
        self.historyList.addItem("history3")
        self.historyList.itemClicked.connect(self.historyListClicked)

        self.verticalLayout.addWidget(self.historyList)



        self.setCentralWidget(self.verticalLayoutWidget)
        self.retranslateUi(self)
        QMetaObject.connectSlotsByName(self)


    def retranslateUi(self, MainWindow):
        _translate = QCoreApplication.translate
        MainWindow.setWindowTitle(_translate("MainWindow", "MainWindow"))

    def historyListClicked(self,item):
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
    window = history_selection()
    window.show()

    sys.exit(app.exec())