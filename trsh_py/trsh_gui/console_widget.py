# class representing the command line text input in the trshell application
from tkinter import END
from PyQt6.QtWidgets import QApplication, QPlainTextEdit
from PyQt6.QtCore import Qt, QMimeData
from PyQt6.QtGui import QTextCursor, QKeySequence, QKeyEvent
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
        self.init_properties()
        self.cursor_lock_pos = 0
        self.wrapper = Wrapper(self)

    def init_appearance(self):
        self.setCursorWidth(CURSOR_WIDTH)

    # init properties fo the text field
    def init_properties(self):
        self.setUndoRedoEnabled(False)

    # returns the last line in the console widget
    def get_last_line(self):
        return self.toPlainText().rsplit('\n',1)[-1].rstrip()

    # returns the current cursor position
    def get_cursor_position(self):
        return self.textCursor().position()

    # checks for cursor at ileagal position
    def is_ilegal_operation(self):
        return self.get_cursor_position() <= self.cursor_lock_pos

    # sets the cursor of the console to the end
    def set_cursor_to_end(self):
        end_cur = self.textCursor()
        end_cur.movePosition(QTextCursor.MoveOperation.End, QTextCursor.MoveMode.MoveAnchor)
        self.setTextCursor(end_cur)

    # appends plain text to the text box
    def appendPlainText(self, string):
        super().appendPlainText(string)
        self.set_cursor_to_end()
        self.cursor_lock_pos = self.get_cursor_position()

    # handle paste actions as well as drag n drop
    def insertFromMimeData(self, source):
        self.set_cursor_to_end()
        return super().insertFromMimeData(source)

    # handle special keypresses
    def keyPressEvent(self, event: QKeyEvent):

        # enter key pressed -> sendprint("Key pressed!") to shell
        if event.key() == Qt.Key.Key_Return:
            self.wrapper.push_to_shell(self.get_last_line())
            return

        # backspace pressed
        if event.key() == Qt.Key.Key_Backspace and self.is_ilegal_operation():
            return

        # delete pressed
        if event.key() == Qt.Key.Key_Delete and self.is_ilegal_operation():
            return

        # left arrow key pressed -> check cursor lock breach
        if event.key() == Qt.Key.Key_Left and self.is_ilegal_operation():
            return

        # up arrow pressed
        if event.key() == Qt.Key.Key_Up:
            return

        # down arrow pressed 
        if event.key() == Qt.Key.Key_Down:
            return

        return super().keyPressEvent(event)
