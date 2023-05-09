import sys

from PyQt6.QtCore import *
from PyQt6.QtGui import *
from PyQt6.QtWidgets import *


class CommitDialog(QMainWindow):
    def __init__(self):
        super(CommitDialog, self).__init__()

        self.centralwidget = QWidget()


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
        self.label.setText("Please enter a summary and \ndescription for progress storage.")
        self.verticalLayout.addWidget(self.label)

        self.pushButton = QPushButton(self.centralwidget)
        self.pushButton.clicked.connect(self.takeinputs)
        self.verticalLayout.addWidget(self.pushButton)




        self.setCentralWidget(self.verticalLayoutWidget)
        self.retranslateUi(self)
        QMetaObject.connectSlotsByName(self)

    def retranslateUi(self, MainWindow):
        _translate = QCoreApplication.translate
        MainWindow.setWindowTitle(_translate("MainWindow", "MainWindow"))
        self.pushButton.setText(_translate("MainWindow", "Proceed"))

    def takeinputs(self):
        ###########################
        ###########################
        # ADD ADDITIONAL CODE HERE!#
        ###########################
        ###########################
        # summary, description stores as str
        _translate = QCoreApplication.translate

        if self.bool:

            self.hide()
        else:
            summary, done1 = QInputDialog.getText(
                self, 'Input Dialog', 'Enter summary:')

            description, done2 = QInputDialog.getText(
                self, 'Input Dialog', 'Enter Description')

            self.bool = True
            self.pushButton.setText(_translate("MainWindow", "Done"))
            if done1 and done2:
                # Showing confirmation message along
                # with information provided by user.
                self.label.setText('Progress Saved Successfully\nName: '
                                   + str(summary) + ', Summary: ' + str(description))






    ################must replace space with _
