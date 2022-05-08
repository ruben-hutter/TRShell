# class representing the main window of the trshell application
from PyQt6.QtWidgets import QWidget
from PyQt6.QtGui import QIcon
import trsh_gui.qss_reader as qss_reader
from trsh_gui.console_widget import ConsoleWidget

STYLE_SHEET = "trsh_gui/main_window.qss"
DEFAULT_WIDTH = 800
DEFAULT_HEIGHT = 500
DEFAULT_UPPER_LEFT_X = 500
DEFAULT_UPPER_LEFT_Y = 200
ICON_FILE = ""
TITLE = "TRShell"

class MainWindow(QWidget):
    def __init__(self):
        # construct main window
        super().__init__()
        self.setWindowTitle(TITLE)
        self.setWindowIcon(QIcon(ICON_FILE))
        self.setGeometry(
            DEFAULT_UPPER_LEFT_X,
            DEFAULT_UPPER_LEFT_Y,
            DEFAULT_WIDTH,
            DEFAULT_HEIGHT
            )
        # apply style sheet
        self.style_sheet = qss_reader.read_style_sheet(STYLE_SHEET)
        self.setStyleSheet(self.style_sheet)

    # kill all wrappers on close
    def closeEvent(self, a0):
        for console_widget in self.findChildren(ConsoleWidget):
            wrapper = console_widget.wrapper
            if not wrapper:
                continue
            wrapper.kill()
        return super().closeEvent(a0)
