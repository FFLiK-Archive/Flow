
from PySide6.QtCore import (QCoreApplication, QDate, QDateTime, QLocale,
    QMetaObject, QObject, QPoint, QRect,
    QSize, QTime, QUrl, Qt)
from PySide6.QtGui import (QBrush, QColor, QConicalGradient, QCursor,
    QFont, QFontDatabase, QGradient, QIcon,
    QImage, QKeySequence, QLinearGradient, QPainter,
    QPalette, QPixmap, QRadialGradient, QTransform)
from PySide6.QtWidgets import (QApplication, QDialog, QHBoxLayout, QLabel,
    QPushButton, QSizePolicy, QVBoxLayout, QWidget)

class Ui_ChooseDialogue(object):
    def __init__(self, ChooseDialogue):
        if not ChooseDialogue.objectName():
            ChooseDialogue.setObjectName(u"ChooseDialogue")
        ChooseDialogue.resize(1168, 728)
        self.verticalLayoutWidget = QWidget(ChooseDialogue)
        self.verticalLayoutWidget.setObjectName(u"verticalLayoutWidget")
        self.verticalLayoutWidget.setGeometry(QRect(470, 280, 218, 80))
        self.verticalLayout = QVBoxLayout(self.verticalLayoutWidget)
        self.verticalLayout.setObjectName(u"verticalLayout")
        self.verticalLayout.setContentsMargins(0, 0, 0, 0)
        self.label = QLabel(self.verticalLayoutWidget)
        self.label.setObjectName(u"label")

        self.verticalLayout.addWidget(self.label)

        self.horizontalLayout = QHBoxLayout()
        self.horizontalLayout.setObjectName(u"horizontalLayout")
        self.FolderButton = QPushButton(self.verticalLayoutWidget)
        self.FolderButton.setObjectName(u"FolderButton")

        self.horizontalLayout.addWidget(self.FolderButton)

        self.FileButton = QPushButton(self.verticalLayoutWidget)
        self.FileButton.setObjectName(u"FileButton")

        self.horizontalLayout.addWidget(self.FileButton)


        self.verticalLayout.addLayout(self.horizontalLayout)


        self.retranslateUi(ChooseDialogue)

        QMetaObject.connectSlotsByName(ChooseDialogue)
    # setupUi

    def retranslateUi(self, ChooseDialogue):
        ChooseDialogue.setWindowTitle(QCoreApplication.translate("ChooseDialogue", u"Dialog", None))
        self.label.setText(QCoreApplication.translate("ChooseDialogue", u"Choose the type of your project.", None))
        self.FolderButton.setText(QCoreApplication.translate("ChooseDialogue", u"Folder", None))
        self.FileButton.setText(QCoreApplication.translate("ChooseDialogue", u"File", None))
    # retranslateUi

