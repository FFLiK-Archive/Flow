import sys
from PyQt6.QtCore import *
from PyQt6.QtGui import *
from PyQt6.QtWidgets import *

from mainui import *
from firstpageui import *
from filetypeselecter import *



if __name__ == '__main__':
    # Create the QApplication
    app = QApplication(sys.argv)
    window = Ui_Dialog()
    window.show()

    sys.exit(app.exec())