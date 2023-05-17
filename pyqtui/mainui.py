import sys
from PyQt6.QtCore import *
from PyQt6.QtGui import *
from PyQt6.QtWidgets import *

import branchactionmenu
import branchselection
import commitnamedialog
import historyactionmenu
import historyselection
from firstpageui import *
from filetypeselecter import *
from commitnamedialog import *
from branchactionmenu import *
from historyactionmenu import *

import flow

class Ui_MainWindow(QMainWindow):
    def __init__(self):
        super(Ui_MainWindow, self).__init__()
        with open(
                file="./style.txt", mode="r"
        ) as f:
            self.setStyleSheet(f.read())
        #with open(
        #        file="./style.txt", mode="r"
        #) as f:
        #    self.setStyleSheet(f.read())

        self.storage_dialog = commitnamedialog.CommitDialog(self)
        self.bmenu = branchactionmenu.branch_menu(self)
        self.hmenu = historyactionmenu.history_menu(self)

        # self.br = "err"
        # self.hs = "err"
        self.NewSubBranchButtonBool = False
        self.centralwidget = QWidget()
        self.centralwidget.setObjectName(u"centralwidget")

        self.horizontalLayout_9 = QHBoxLayout(self.centralwidget)
        self.horizontalLayout_9.setObjectName(u"horizontalLayout_9")
        self.verticalLayout = QVBoxLayout()
        self.verticalLayout.setObjectName(u"verticalLayout")
        self.Logo = QLabel(self.centralwidget)
        self.Logo.setObjectName(u"Logo")
        pixmap = QPixmap('logo.png')
        pixmap = pixmap.scaled(50,50, transformMode = Qt.TransformationMode.SmoothTransformation)
        self.Logo.setPixmap(pixmap)

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


###############################################
        self.BranchList = QListWidget(self.centralwidget)
        self.BranchList.setObjectName(u"BranchList")
        self.BranchList.itemClicked.connect(self.BranchListSelected)
        self.BranchList.itemDoubleClicked.connect(self.BranchListClicked)

        self.verticalLayout_2.addWidget(self.BranchList)

        # self.NewSubBranchButton = QPushButton(self.centralwidget)
        # self.NewSubBranchButton.setObjectName(u"NewSubBranchButton")
        # self.NewSubBranchButton.setCheckable(False)
        # self.NewSubBranchButton.setFlat(False)
        # self.NewSubBranchButton.clicked.connect(self.NewSubBranchButtonClicked)
        #
        # self.verticalLayout_2.addWidget(self.NewSubBranchButton)

        # self.horizontalLayout_3 = QHBoxLayout()
        # self.horizontalLayout_3.setObjectName(u"horizontalLayout_3")
        # self.MergeButton = QPushButton(self.centralwidget)
        # self.MergeButton.setObjectName(u"MergeButton")
        # self.MergeButton.clicked.connect(self.MergeButtonClicked)
        #
        # self.horizontalLayout_3.addWidget(self.MergeButton)
        #
        # self.ReplaceButton = QPushButton(self.centralwidget)
        # self.ReplaceButton.setObjectName(u"ReplaceButton")
        #
        # self.horizontalLayout_3.addWidget(self.ReplaceButton)
        #
        # self.verticalLayout_2.addLayout(self.horizontalLayout_3)
        #
        # self.DeleteButton = QPushButton(self.centralwidget)
        # self.DeleteButton.setObjectName(u"DeleteButton")
        #
        # self.verticalLayout_2.addWidget(self.DeleteButton)

        self.horizontalLayout.addLayout(self.verticalLayout_2)

        self.verticalLayout_3 = QVBoxLayout()
        self.verticalLayout_3.setObjectName(u"verticalLayout_3")
        self.HistoryLabel = QLabel(self.centralwidget)
        self.HistoryLabel.setObjectName(u"HistoryLabel")

        self.verticalLayout_3.addWidget(self.HistoryLabel)


################################
        self.HistoryList = QListWidget(self.centralwidget)
        self.HistoryList.setObjectName(u"HistoryList")
        self.HistoryList.itemDoubleClicked.connect(self.HistoryListClicked)
        self.HistoryList.itemClicked.connect(self.DisableSelecting)

        self.verticalLayout_3.addWidget(self.HistoryList)

        self.CommitButton = QPushButton(self.centralwidget)
        self.CommitButton.setObjectName(u"CommitButton")
        self.CommitButton.clicked.connect(self.CommitButtonClicked)

        self.verticalLayout_3.addWidget(self.CommitButton)

        self.horizontalLayout.addLayout(self.verticalLayout_3)

        self.verticalLayout_4 = QVBoxLayout()
        self.verticalLayout_4.setObjectName(u"verticalLayout_4")
        self.ChangeLogLabel = QLabel(self.centralwidget)
        self.ChangeLogLabel.setObjectName(u"ChangeLogLabel")

        self.verticalLayout_4.addWidget(self.ChangeLogLabel)


####################################
        self.ChangeLogList = QListWidget(self.centralwidget)
        self.ChangeLogList.setObjectName(u"ChangeLogList")
        self.ChangeLogList.itemClicked.connect(self.DisableSelecting)

        self.verticalLayout_4.addWidget(self.ChangeLogList)

        self.RefreshButton = QPushButton(self.centralwidget)
        self.RefreshButton.setObjectName(u"RefreshButton")
        self.RefreshButton.clicked.connect(self.RefreshButtonClicked)

        self.verticalLayout_4.addWidget(self.RefreshButton)

        self.horizontalLayout.addLayout(self.verticalLayout_4)

        self.verticalLayout.addLayout(self.horizontalLayout)

        self.StatusLabel = QLabel(self.centralwidget)
        self.StatusLabel.setObjectName(u"StatusLabel")

        self.verticalLayout.addWidget(self.StatusLabel)

        self.horizontalLayout_9.addLayout(self.verticalLayout)

        self.setCentralWidget(self.centralwidget)
        self.menubar = QMenuBar()
        self.menubar.setObjectName(u"menubar")
        self.menubar.setGeometry(QRect(0, 0, 1168, 37))
        self.setMenuBar(self.menubar)
        self.statusbar = QStatusBar()
        self.statusbar.setObjectName(u"statusbar")
        self.setStatusBar(self.statusbar)

        self.retranslateUi(self)

        # self.NewSubBranchButton.setDefault(False)
        QMetaObject.connectSlotsByName(self)

    # setupUi

    def retranslateUi(self, MainWindow):
        MainWindow.setWindowTitle(QCoreApplication.translate("MainWindow", u"Flow", None))
        # self.Logo.setText(QCoreApplication.translate("MainWindow", u"Flow", None))
        self.ProjectNameLabel.setText(QCoreApplication.translate("MainWindow", u"Project Name", None))
        self.BranchLabel.setText(QCoreApplication.translate("MainWindow", u"Branch", None))
        # self.NewSubBranchButton.setText(QCoreApplication.translate("MainWindow", u"New Sub Branch", None))
        # self.MergeButton.setText(QCoreApplication.translate("MainWindow", u"Merge", None))
        # self.ReplaceButton.setText(QCoreApplication.translate("MainWindow", u"Replace", None))
        # self.DeleteButton.setText(QCoreApplication.translate("MainWindow", u"Delete", None))
        self.HistoryLabel.setText(QCoreApplication.translate("MainWindow", u"History", None))
        self.CommitButton.setText(QCoreApplication.translate("MainWindow", u"Save Progress", None))
        self.ChangeLogLabel.setText(QCoreApplication.translate("MainWindow", u"Change Log", None))
        self.RefreshButton.setText(QCoreApplication.translate("MainWindow", u"Refresh", None))
        #self.StatusLabel.setText(QCoreApplication.translate("MainWindow", u"Status...", None))
    # retranslateUi
    def hideEvent(self, event):
        #quit(0)
        pass

    # setting UI values
    def SetUIData(self):
        self.SetBranchList()
        self.SetChangeLog()
        self.SetHistoryList()
        name, ret = flow.command(["get_name"], 1)
        self.ProjectNameLabel.setText(QCoreApplication.translate("MainWindow", name[0][0], None))


    def SetBranchList(self):
        self.BranchList.clear()
        flow.branch_list, ret = flow.command(["get_branch"], 4)
        if ret: return
        for i in range(len(flow.branch_list)):
            dat = flow.branch_list[i][1] + "\n> "
            for j in range(len(flow.branch_list)):
                if flow.branch_list[j][flow.BRANCH_ID] == flow.branch_list[i][flow.BRANCH_ORIGIN_ID]:
                    dat += flow.branch_list[j][flow.BRANCH_NAME]
                    break
            else:
                dat += "(Main Branch)"
            self.BranchList.addItem(dat)

        data, ret = flow.command(["get_activated_branch"], 1)
        if ret: return
        for i in range(0, len(flow.branch_list)):
            if flow.branch_list[i][flow.BRANCH_ID] == data[0][0]:
                self.BranchList.item(i).setSelected(True)
                flow.activated_branch = i
                break

    def SetHistoryList(self):
        self.HistoryList.clear()
        flow.history_list, ret = flow.command(['get_history'], 3)
        if ret: return
        for i in range(0, len(flow.history_list)):
            self.HistoryList.addItem(flow.history_list[i][0] + "\n> " + flow.history_list[i][1])
    
    def SetChangeLog(self):
        self.ChangeLogList.clear()
        flow.change_log, ret = flow.command(['get_change_log'], 2)
        if ret: return
        for i in range(len(flow.change_log)):
            self.ChangeLogList.addItem(flow.change_log[i][0] + " : " + flow.change_log[i][1])

    def DisableSelecting(self, item):
        item.setSelected(False)

    def BranchListSelected(self, item):
        index = self.BranchList.currentRow()
        ret = flow.command(['activate_branch', flow.branch_list[index][flow.BRANCH_ID]])
        if ret: return
        self.SetUIData()

    def BranchListClicked(self, item):
        print(item.text())
        self.bmenu.show()

    def HistoryListClicked(self, item):
        index = self.HistoryList.currentRow()
        self.hmenu.SetIndex(index)
        self.hmenu.show()

    def CommitButtonClicked(self):
        print("Progress Saved!")
        self.storage_dialog.show()


    def RefreshButtonClicked(self):
        self.SetChangeLog()
        print("Refreshing!")

    # def NewSubBranchButtonClicked(self):
    #     print("NewSubBranchButtonClicked")
    #
    # def MergeButtonClicked(self):
    #     print("MergeButtonClicked")
