from PySide6.QtWidgets import QApplication, QMainWindow
from ui_mainwindow import Ui_MainWindow

messages = []

class MainWindow(QMainWindow):
    def __init__(self, parent=None):
        super(MainWindow, self).__init__(parent)
        self.ui = Ui_MainWindow()
        self.ui.setupUi(self)
        self.ui.send.clicked.connect(self.hello)

    def hello(self):
        text = self.ui.text.text()
        messages.append(text)
        temp = ""
        for i in messages:
            temp = temp + i + "\n"
        self.ui.chat.setText(temp)