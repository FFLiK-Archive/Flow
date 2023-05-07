from PySide6.QtCore import (QCoreApplication, QDate, QDateTime, QLocale,
    QMetaObject, QObject, QPoint, QRect,
    QSize, QTime, QUrl, Qt)
from PySide6.QtGui import (QBrush, QColor, QConicalGradient, QCursor,
    QFont, QFontDatabase, QGradient, QIcon,
    QImage, QKeySequence, QLinearGradient, QPainter,
    QPalette, QPixmap, QRadialGradient, QTransform)
from PySide6.QtWidgets import (QApplication, QDialog, QHBoxLayout, QLabel,
    QPushButton, QSizePolicy, QVBoxLayout, QWidget)

from mainwindowui import *
from firstpageui import *
from filetypeselecter import *

if __name__ == '__main__':
    # Create the QApplication
    app = QApplication(sys.argv)
    MainWindow = QMainWindow()
    window = Ui_MainWindow(MainWindow)
    MainWindow.show()
    
    sys.exit(app.exec())




