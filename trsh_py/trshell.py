import sys
from wrapper import Wrapper
from PyQt6.QtWidgets import QApplication
import trsh_gui.gui_builder as gui_builder

class TRShell:
    def __init__(self):
        self.init_gui()
    
    # init the gui components
    def init_gui(self):
        self.application = QApplication(sys.argv)
        # init main window
        self.window = gui_builder.assemble_gui()
        
    # launch the gui starting the application
    def launch_gui(self):
        if self.window:
            self.window.show()
        sys.exit(self.application.exec())

if __name__ == "__main__":
    shell = TRShell()
    shell.launch_gui()