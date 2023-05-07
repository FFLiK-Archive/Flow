
from PySide6.QtCore import (QCoreApplication, QDate, QDateTime, QLocale,
    QMetaObject, QObject, QPoint, QRect,
    QSize, QTime, QUrl, Qt)
from PySide6.QtGui import (QBrush, QColor, QConicalGradient, QCursor,
    QFont, QFontDatabase, QGradient, QIcon,
    QImage, QKeySequence, QLinearGradient, QPainter,
    QPalette, QPixmap, QRadialGradient, QTransform)
from PySide6.QtWidgets import (QApplication, QDialog, QHBoxLayout, QLabel,
    QPushButton, QSizePolicy, QVBoxLayout, QWidget)

class Ui_Dialog(object):
    def __init__(self, Dialog):
        if not Dialog.objectName():
            Dialog.setObjectName(u"Dialog")
        Dialog.resize(1168, 728)
        self.verticalLayoutWidget = QWidget(Dialog)
        self.verticalLayoutWidget.setObjectName(u"verticalLayoutWidget")
        self.verticalLayoutWidget.setGeometry(QRect(530, 230, 218, 80))
        self.verticalLayout = QVBoxLayout(self.verticalLayoutWidget)
        self.verticalLayout.setObjectName(u"verticalLayout")
        self.verticalLayout.setContentsMargins(0, 0, 0, 0)
        self.logo = QLabel(self.verticalLayoutWidget)
        self.logo.setObjectName(u"logo")

        self.verticalLayout.addWidget(self.logo)

        self.horizontalLayout = QHBoxLayout()
        self.horizontalLayout.setObjectName(u"horizontalLayout")
        self.OpenButton = QPushButton(self.verticalLayoutWidget)
        self.OpenButton.setObjectName(u"OpenButton")

        self.horizontalLayout.addWidget(self.OpenButton)

        self.NewButton = QPushButton(self.verticalLayoutWidget)
        self.NewButton.setObjectName(u"NewButton")

        self.horizontalLayout.addWidget(self.NewButton)


        self.verticalLayout.addLayout(self.horizontalLayout)


        self.retranslateUi(Dialog)

        QMetaObject.connectSlotsByName(Dialog)
    # setupUi

    def retranslateUi(self, Dialog):
        Dialog.setWindowTitle(QCoreApplication.translate("Dialog", u"Dialog", None))
        self.logo.setText(QCoreApplication.translate("Dialog", u"Flow", None))
        self.OpenButton.setText(QCoreApplication.translate("Dialog", u"Open", None))
        self.NewButton.setText(QCoreApplication.translate("Dialog", u"New", None))
    # retranslateUi

