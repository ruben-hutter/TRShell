import os
import tkinter as tk
from tkinter import Label, Text, Entry, StringVar
from threading import Thread
import time

VERSION = '0.1'
FONT = 'Consolas 12'
BACKGROUND = '#272626'
FOREGROUND = 'white'
SIZE = '750x600'

class TRShell:
    # inti the tkinter window
    def init_window(self):
        # init tkinter window
        self.window = tk.Tk()
        self.window.title('TRS Shell version ' + VERSION)
        self.window.geometry(SIZE)
        self.window.configure(background=BACKGROUND)
        
        # init text field
        self.cli = tk.Text(self.window, height='10', width='75', font=FONT, background=BACKGROUND,
                         foreground=FOREGROUND,
                         insertbackground=FOREGROUND)
        self.cli.pack()

    # construct new trshell object
    def __init__(self):
        self.init_window()

    # launches the cli
    def launch(self):
        self.window.mainloop()

    # prints a string to the cli
    def print(self, text):
        print(text)

def print_ur_mom(shell):
    for i in range (10):
        time.sleep(1)
        shell.print("Dis Mami")

if __name__ == '__main__':
    shell = TRShell()
    shell.launch()