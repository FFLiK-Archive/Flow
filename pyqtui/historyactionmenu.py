import sys

from PyQt6.QtCore import *
from PyQt6.QtGui import *
from PyQt6.QtWidgets import *
import happyhappyhappy

from historyselection import *
import historyselection

class history_menu(QMainWindow):
    def __init__(self):
        super(history_menu, self).__init__()

        self.fuckyeah = happyhappyhappy.happy()

        self.hselection = historyselection.history_selection()

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

    def retranslateUi(self, MainWindow):
        _translate = QCoreApplication.translate
        MainWindow.setWindowTitle(_translate("MainWindow", "MainWindow"))
        self.RevertButton.setText(_translate("MainWindow", "Revert"))
        self.DeleteButton.setText(_translate("MainWindow", "Delete"))

    def RevertButtonClicked(self):
        ###########################
        ###########################
        #ADD ADDITIONAL CODE HERE!#
        ###########################
        ###########################
        print("RevertButtonClicked")
        self.fuckyeah.show()
        self.hide()
    def DeleteButtonClicked(self):
        ###########################
        ###########################
        # ADD ADDITIONAL CODE HERE!#
        ###########################
        ###########################
        print("DeleteButtonClicked")
        self.fuckyeah.show()
        self.hide()

if __name__ == '__main__':
    # Create the QApplication
    app = QApplication(sys.argv)
    window = history_menu()
    window.show()

    sys.exit(app.exec())