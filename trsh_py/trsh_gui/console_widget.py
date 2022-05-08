# class representing the command line text input in the trshell application
from PyQt6.QtWidgets import QApplication, QPlainTextEdit
from PyQt6.QtCore import Qt
from wrapper import Wrapper
import trsh_gui.qss_reader as qss_reader

STYLE_SHEET = "trsh_gui/console_widget.qss"
CURSOR_WIDTH = 10

class ConsoleWidget(QPlainTextEdit):
    def __init__(self):
        super().__init__()
        self.style_sheet = qss_reader.read_style_sheet(STYLE_SHEET)
        self.setStyleSheet(self.style_sheet)
        self.init_appearance()
        self.wrapper = Wrapper(self)

    def init_appearance(self):
        self.setCursorWidth(CURSOR_WIDTH)

    def get_last_line(self):
        return self.toPlainText().rsplit('\n',1)[-1].rstrip()

    # handle special keypresses
    def keyPressEvent(self, event):
        # enter key pressed -> sendprint("Key pressed!") to shell
        if event.key() == Qt.Key.Key_Return:
            self.wrapper.push_to_shell(self.get_last_line())
            return
        return super().keyPressEvent(event)
