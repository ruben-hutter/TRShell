# wrapper wrapping the trshell c implementation into python
import subprocess as sp
from threading import Thread
from turtle import update
from PyQt6.QtGui import *
from PyQt6.QtWidgets import *
from PyQt6.QtCore import *

SHELL_EXEC_PATH = 'dummy_shell.o'
SHELL_WRAP_FLAG = '-w'

class Wrapper:
    # construct new trshell object
    def __init__(self, console_widget):
        self.console_widget = console_widget
        self.shell = None
        self.run_shell()

    # destructor of wrapper
    def __del__(self):
        self.kill()
    
    # terminates the trshell task and the trshell reader
    def kill(self):
        if self.shell_reader:
            self.shell_reader.signals.send_kill()
        if self.shell:
            self.shell.terminate()
            try:
                self.shell.wait(3)
            except:
                self.shell.kill()
    
    # launches a new trshell c process
    def run_shell(self):
        # launch shell c with subprocess 
        command = "./" + SHELL_EXEC_PATH + ' ' + SHELL_WRAP_FLAG
        self.shell = sp.Popen(
            command,
            stdin=sp.PIPE,
            stdout=sp.PIPE,
            stderr=sp.PIPE,
            shell=True
            )

        # redirect stdout of subprocess to gui
        self.launch_shell_reader()

    # creates and starts a new qrunnable reading from the shell process
    def launch_shell_reader(self):
        self.shell_reader = ShellReader(self.shell)
        self.shell_reader.signals.output_signal.connect(self.update_gui)
        QThreadPool.globalInstance().start(self.shell_reader)
        return

    # sends the received text to the console widget
    def update_gui(self, output_string):
        self.console_widget.appendPlainText(output_string)
        return

    # pushes a string to the trshell c process
    def push_to_shell(self, input_string):
        input_string = input_string + '\n'
        self.shell.stdin.write(input_string.encode())
        self.shell.stdin.flush()

class ShellReader(QRunnable):
    # init new shell reader
    def __init__(self, shell):
        super(ShellReader, self).__init__()
        self.shell = shell
        self.signals = ShellReaderSignals()

    # reads the str out of the shell process and calls push_to_gui
    @pyqtSlot()
    def run(self):
        while not self.signals.kill_signal:
            output_string = self.read_line_from_shell()
            if not output_string:
                break
            output_string = output_string
            self.push_to_gui(output_string)

    # read line from shell
    def read_line_from_shell(self):
        return self.shell.stdout.readline().decode()

    # pushes a string to the quee for the qui to print it
    def push_to_gui(self, output_string):
        self.signals.output_signal.emit(output_string)

# class of all signals that are used for the shellreader to communicate with the wrapper
class ShellReaderSignals(QObject):
    output_signal = pyqtSignal(str)
    kill_signal = False

    def send_kill(self):
        kill_signal = True
    