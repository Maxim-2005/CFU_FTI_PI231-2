# -*- coding: utf-8 -*-

################################################################################
## Form generated from reading UI file 'FormBUmnSq.ui'
##
## Created by: Qt User Interface Compiler version 6.6.2
##
## WARNING! All changes made in this file will be lost when recompiling UI file!
################################################################################

from PySide6.QtCore import (QCoreApplication, QDate, QDateTime, QLocale,
    QMetaObject, QObject, QPoint, QRect,
    QSize, QTime, QUrl, Qt)
from PySide6.QtGui import (QBrush, QColor, QConicalGradient, QCursor,
    QFont, QFontDatabase, QGradient, QIcon,
    QImage, QKeySequence, QLinearGradient, QPainter,
    QPalette, QPixmap, QRadialGradient, QTransform)
from PySide6.QtWidgets import (QApplication, QLabel, QMainWindow, QMenuBar,
    QPlainTextEdit, QPushButton, QScrollArea, QSizePolicy,
    QStatusBar, QWidget)

class Form(object):
    def setupUi(self, MainWindow):
        if not MainWindow.objectName():
            MainWindow.setObjectName(u"MainWindow")
        MainWindow.resize(386, 600)
        self.centralwidget = QWidget(MainWindow)
        self.centralwidget.setObjectName(u"centralwidget")
        self.scrollArea = QScrollArea(self.centralwidget)
        self.scrollArea.setObjectName(u"scrollArea")
        self.scrollArea.setGeometry(QRect(10, 10, 371, 481))
        self.scrollArea.setWidgetResizable(True)
        self.scrollAreaWidgetContents = QWidget()
        self.scrollAreaWidgetContents.setObjectName(u"scrollAreaWidgetContents")
        self.scrollAreaWidgetContents.setGeometry(QRect(0, 0, 369, 479))
        self.label_01 = QLabel(self.scrollAreaWidgetContents)
        self.label_01.setObjectName(u"label_01")
        self.label_01.setGeometry(QRect(260, 30, 91, 20))
        self.label_02 = QLabel(self.scrollAreaWidgetContents)
        self.label_02.setObjectName(u"label_02")
        self.label_02.setGeometry(QRect(20, 50, 101, 41))
        self.scrollArea.setWidget(self.scrollAreaWidgetContents)
        self.TextEdit = QPlainTextEdit(self.centralwidget)
        self.TextEdit.setObjectName(u"TextEdit")
        self.TextEdit.setGeometry(QRect(10, 510, 271, 51))
        self.send = QPushButton(self.centralwidget)
        self.send.setObjectName(u"send")
        self.send.setGeometry(QRect(300, 510, 75, 24))
        MainWindow.setCentralWidget(self.centralwidget)
        self.menubar = QMenuBar(MainWindow)
        self.menubar.setObjectName(u"menubar")
        self.menubar.setGeometry(QRect(0, 0, 386, 22))
        MainWindow.setMenuBar(self.menubar)
        self.statusbar = QStatusBar(MainWindow)
        self.statusbar.setObjectName(u"statusbar")
        MainWindow.setStatusBar(self.statusbar)

        self.retranslateUi(MainWindow)

        QMetaObject.connectSlotsByName(MainWindow)
    # setupUi

    def retranslateUi(self, MainWindow):
        MainWindow.setWindowTitle(QCoreApplication.translate("MainWindow", u"MainWindow", None))
        self.label_01.setText(QCoreApplication.translate("MainWindow", u"\u041f\u0440\u0438\u0432\u0435\u0442!", None))
        self.label_02.setText(QCoreApplication.translate("MainWindow", u"\u0421\u0430\u043c \u0442\u044b \u041f\u0440\u0438\u0432\u0435\u0442!", None))
        self.send.setText(QCoreApplication.translate("MainWindow", u"send", None))
    # retranslateUi

