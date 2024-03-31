from PySide6.QtWidgets import QApplication, QMainWindow
from ui_mainwindow import Ui_Form
from chat import chat

class MainWindow(QMainWindow):
    def __init__(self, parent=None):
        super(MainWindow, self).__init__(parent)
        self.ui = Ui_Form()
        self.ui.setupUi(self)
        self.upMessages()
        
        self.ui.send.clicked.connect(self.send) # Надо добавить кнопку
        self.ui.friends.clicked.connect(self.friends)
        self.ui.notifications_active.clicked.connect(self.notifications_active)
        self.ui.settings.clicked.connect(self.settings) # Настройки +
        self.ui.theme.clicked.connect(self.theme) # Темы +
        self.ui.user.clicked.connect(self.user) # Пользователь +
        self.ui.profile.clicked.connect(self.profile) # Профиль +
        self.ui.menu.clicked.connect(self.menu) # Меню +

    # Отправить сообщение
    def send(self):
        text = self.ui.message.text()
        chat.append(text)
        self.ui.message.setText("")
        self.upMessages()

    def upMessages(self):
        msg = "start\n"
        for i in chat:
            msg = msg + i + "\n"
        self.ui.messages.setText(msg)

    # Открыть список друзей
    def friends(self):
        print("Friends")
        
    # Посмореть уведомления
    def notifications_active(self):
        print("notifications_active")
        
    # Настройки
    def settings(self):
        print("settings")
    
    # Темы
    def theme(self):
        print("theme")

    # Пользователь
    def user(self):
        print("user")
        
    # Профиль
    def profile(self):
        print("profile")
        
    # Меню
    def menu(self):
        print("menu")