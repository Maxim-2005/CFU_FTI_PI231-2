 # !/usr/bin/env python
 # Мой проект AuxProg

import sys
from PySide6 import QtWidgets
from Main import Main

if __name__ == '__main__':
    app = QtWidgets.QApplication(sys.argv)
    main = Main()
    sys.exit(app.exec_())