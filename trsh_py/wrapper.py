# wrapper wrapping the trshell c implementation into python
import subprocess as sp
from threading import Thread
import sys
from time import sleep

SHELL_EXEC_PATH = "dummy_shell.o"

class Wrapper:
    # pushes a string to the qui
    def push_to_gui(self, output_string):

        # debug printout
        print(f"Subprocess sent: {output_string}")

    # reads the str out of the shell process and calls push_to_gui
    def read_shell_stdout(self):
        while True:
            output_string = self.shell.stdout.read(1).decode()
            if output_string == '' and self.shell.poll() != None:
                break
            self.push_to_gui(output_string)

    # launches a new trshell c process
    def run_shell(self):
        # launch shell c with subprocess 
        command = "./" + SHELL_EXEC_PATH
        self.shell = sp.Popen(
            command,
            stdin=sp.PIPE,
            stdout=sp.PIPE,
            stderr=sp.PIPE,
            shell=True
            )

        # redirect stdout of subprocess to gui
        stdout_reader = Thread(target=self.read_shell_stdout)
        stdout_reader.setDaemon(True)
        sleep(10)
        stdout_reader.start()

    # pushes a string to the trshell c process
    def push_to_shell(self, input_string):
        self.shell.communicate(input=input_string.encode())
        return
        
    # construct new trshell object
    def __init__(self, gui_section):
        self.gui_section = gui_section
        self.shell = None
        self.run_shell()

    # terminate terminal on destruction of wrapper
    def __del__(self):
        if self.shell == None:
            return
        self.shell.terminate()
        if self.shell != None and self.shell.poll() == None:
            self.shell.kill()
