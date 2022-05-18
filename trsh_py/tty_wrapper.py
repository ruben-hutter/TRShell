import os
import pty
import tty
import subprocess
import sys
from PyQt6.QtGui import *
from PyQt6.QtWidgets import *
from PyQt6.QtCore import *
from numpy import byte

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
        # setup pty
        self.master_fd, self.slave_fd = pty.openpty()
        #tty.setraw(sys.stdin.fileno())
        command = './' + SHELL_EXEC_PATH + ' ' + SHELL_WRAP_FLAG
   
        self.shell = subprocess.Popen(command,
            stdin=self.slave_fd,
            stdout=self.slave_fd,
            stderr=self.slave_fd,
            # Run in a new process group to enable bash's job control.
            preexec_fn=os.setsid,
            shell=True,
            # Run bash in "dumb" terminal.
            env=dict(os.environ, TERM='dumb')
            )
        
        # redirect pty communication to gui
        self.launch_shell_reader()

    # creates and starts a new qrunnable reading from the shell process
    def launch_shell_reader(self):
        self.shell_reader = FDReader(self.master_fd)
        self.shell_reader.signals.output_signal.connect(self.process_shell_output)
        QThreadPool.globalInstance().start(self.shell_reader)

    # processes the output redeived from the master_fd
    def process_shell_output(self, output_string):
        print(output_string)

    # send string to the shell
    def push_bytes_to_shell(self, input_bytes):
        os.write(self.master_fd, input_bytes)

class FDReader(QRunnable):
    # init new shell reader
    def __init__(self, file_desc):
        super(FDReader, self).__init__()
        self.fd = file_desc
        self.signals = FDReaderSignals()

    # reads the str out of the shell process and calls push_to_gui
    @pyqtSlot()
    def run(self):
        while not self.signals.kill_signal:
            output_string = self.read_line_from_fd()
            if not output_string:
                break
            self.push_to_wrapper(output_string)

    # read line from shell
    def read_line_from_fd(self):
        return os.read(self.fd, 10240)

    # pushes a string to the quee for the qui to print it
    def push_to_wrapper(self, output_string):
        self.signals.output_signal.emit(output_string)

# class of all signals that are used for the shellreader to communicate with the wrapper
class FDReaderSignals(QObject):
    output_signal = pyqtSignal(bytes)
    kill_signal = False

    def send_kill(self):
        kill_signal = True