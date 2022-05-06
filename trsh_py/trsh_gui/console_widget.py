# class representing the command line text in the trshell application
from PyQt6.QtWidgets import QApplication, QPlainTextEdit

import trsh_gui.qss_reader as qss_reader

STYLE_SHEET = "trsh_gui/console_widget.qss"

class ConsoleWidget(QPlainTextEdit):
    def __init__(self):
        super().__init__()
        self.style_sheet = qss_reader.read_style_sheet(STYLE_SHEET)
        self.setStyleSheet(self.style_sheet)

