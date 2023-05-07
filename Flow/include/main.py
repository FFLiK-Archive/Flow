import sys
from PyQt6.QtCore import *
from PyQt6.QtGui import *
from PyQt6.QtWidgets import *

from mainwindowui import *
from firstpageui import *
from filetypeselecter import *


if __name__ == '__main__':
    # Create the QApplication
    app = QApplication(sys.argv)
    MainWindow = QMainWindow()
    window = Ui_Dialog(MainWindow)
    MainWindow.show()

    sys.exit(app.exec())




