import sys
from PyQt6.QtCore import *
from PyQt6.QtGui import *
from PyQt6.QtWidgets import *
from mainwindowui import *
from firstpageui import *
from filetypeselecter import *



class Ui_MainWindow(QMainWindow):
    def __init__(self, MainWindow):
        super()
        
        MainWindow.resize(1168, 728)
        self.centralwidget = QWidget(MainWindow)
        self.centralwidget.setObjectName(u"centralwidget")
        self.horizontalLayout_9 = QHBoxLayout(self.centralwidget)
        self.horizontalLayout_9.setObjectName(u"horizontalLayout_9")
        self.verticalLayout = QVBoxLayout()
        self.verticalLayout.setObjectName(u"verticalLayout")
        self.Logo = QLabel(self.centralwidget)
        self.Logo.setObjectName(u"Logo")

        self.verticalLayout.addWidget(self.Logo)

        self.ProjectNameLabel = QLabel(self.centralwidget)
        self.ProjectNameLabel.setObjectName(u"ProjectNameLabel")

        self.verticalLayout.addWidget(self.ProjectNameLabel)

        self.horizontalLayout = QHBoxLayout()
        self.horizontalLayout.setObjectName(u"horizontalLayout")
        self.verticalLayout_2 = QVBoxLayout()
        self.verticalLayout_2.setObjectName(u"verticalLayout_2")
        self.BranchLabel = QLabel(self.centralwidget)
        self.BranchLabel.setObjectName(u"BranchLabel")

        self.verticalLayout_2.addWidget(self.BranchLabel)

        self.BranchList = QListWidget(self.centralwidget)
        self.BranchList.setObjectName(u"BranchList")
        ###############
        self.BranchList.addItem("hello")
        self.BranchList.addItem("who")
        self.BranchList.addItem("the")
        self.BranchList.addItem("fuck")
        self.BranchList.addItem("are")
        self.BranchList.addItem("you")

        self.verticalLayout_2.addWidget(self.BranchList)


        #################
        self.NewSubBranchButton = QPushButton(self.centralwidget)
        self.NewSubBranchButton.setObjectName(u"NewSubBranchButton")
        self.NewSubBranchButton.setCheckable(False)
        self.NewSubBranchButton.setFlat(False)
        self.NewSubBranchButton.clicked.connect(self.NewSubBranchButtonClicked)

        self.verticalLayout_2.addWidget(self.NewSubBranchButton)

        self.horizontalLayout_3 = QHBoxLayout()
        self.horizontalLayout_3.setObjectName(u"horizontalLayout_3")
        self.MergeButton = QPushButton(self.centralwidget)
        self.MergeButton.setObjectName(u"MergeButton")

        self.horizontalLayout_3.addWidget(self.MergeButton)

        self.ReplaceButton = QPushButton(self.centralwidget)
        self.ReplaceButton.setObjectName(u"ReplaceButton")

        self.horizontalLayout_3.addWidget(self.ReplaceButton)


        self.verticalLayout_2.addLayout(self.horizontalLayout_3)

        self.DeleteButton = QPushButton(self.centralwidget)
        self.DeleteButton.setObjectName(u"DeleteButton")

        self.verticalLayout_2.addWidget(self.DeleteButton)


        self.horizontalLayout.addLayout(self.verticalLayout_2)

        self.verticalLayout_3 = QVBoxLayout()
        self.verticalLayout_3.setObjectName(u"verticalLayout_3")
        self.HistoryLabel = QLabel(self.centralwidget)
        self.HistoryLabel.setObjectName(u"HistoryLabel")

        self.verticalLayout_3.addWidget(self.HistoryLabel)

        self.HistoryList = QListWidget(self.centralwidget)
        self.HistoryList.setObjectName(u"HistoryList")

        self.verticalLayout_3.addWidget(self.HistoryList)

        self.CommitButton = QPushButton(self.centralwidget)
        self.CommitButton.setObjectName(u"CommitButton")

        self.verticalLayout_3.addWidget(self.CommitButton)


        self.horizontalLayout.addLayout(self.verticalLayout_3)

        self.verticalLayout_4 = QVBoxLayout()
        self.verticalLayout_4.setObjectName(u"verticalLayout_4")
        self.ChangeLogLabel = QLabel(self.centralwidget)
        self.ChangeLogLabel.setObjectName(u"ChangeLogLabel")

        self.verticalLayout_4.addWidget(self.ChangeLogLabel)

        self.ChangeLogList = QListWidget(self.centralwidget)
        self.ChangeLogList.setObjectName(u"ChangeLogList")

        self.verticalLayout_4.addWidget(self.ChangeLogList)


        self.horizontalLayout.addLayout(self.verticalLayout_4)


        self.verticalLayout.addLayout(self.horizontalLayout)

        self.StatusLabel = QLabel(self.centralwidget)
        self.StatusLabel.setObjectName(u"StatusLabel")

        self.verticalLayout.addWidget(self.StatusLabel)


        self.horizontalLayout_9.addLayout(self.verticalLayout)

        MainWindow.setCentralWidget(self.centralwidget)
        self.menubar = QMenuBar(MainWindow)
        self.menubar.setObjectName(u"menubar")
        self.menubar.setGeometry(QRect(0, 0, 1168, 37))
        MainWindow.setMenuBar(self.menubar)
        self.statusbar = QStatusBar(MainWindow)
        self.statusbar.setObjectName(u"statusbar")
        MainWindow.setStatusBar(self.statusbar)

        self.retranslateUi(MainWindow)

        self.NewSubBranchButton.setDefault(False)


        QMetaObject.connectSlotsByName(MainWindow)
    # setupUi

    def retranslateUi(self, MainWindow):
        MainWindow.setWindowTitle(QCoreApplication.translate("MainWindow", u"MainWindow", None))
        self.Logo.setText(QCoreApplication.translate("MainWindow", u"Flow", None))
        self.ProjectNameLabel.setText(QCoreApplication.translate("MainWindow", u"Project Name", None))
        self.BranchLabel.setText(QCoreApplication.translate("MainWindow", u"Branch", None))
        self.NewSubBranchButton.setText(QCoreApplication.translate("MainWindow", u"New Sub Branch", None))
        self.MergeButton.setText(QCoreApplication.translate("MainWindow", u"Merge", None))
        self.ReplaceButton.setText(QCoreApplication.translate("MainWindow", u"Replace", None))
        self.DeleteButton.setText(QCoreApplication.translate("MainWindow", u"Delete", None))
        self.HistoryLabel.setText(QCoreApplication.translate("MainWindow", u"History", None))
        self.CommitButton.setText(QCoreApplication.translate("MainWindow", u"Save Progress", None))
        self.ChangeLogLabel.setText(QCoreApplication.translate("MainWindow", u"Change Log", None))
        self.StatusLabel.setText(QCoreApplication.translate("MainWindow", u"Status...", None))
    # retranslateUi

    def NewSubBranchButtonClicked(self):
        print("NewSubBranch Button clicked!")

