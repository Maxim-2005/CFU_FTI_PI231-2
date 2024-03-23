import sys
from PySide6 import QtCore, QtWidgets
from Form import Ui_MainWindow

class Main(Form, QtWidgets.QWidget):
    def __init__(self):
        super().__init__()
        self.setupUi(self)
        self.installEventFilter(self)
        self.show()
        self.send.clicked.connect(self.button_click)
         
    def button_click(self):
        self.label_01.setText("Poka")