# responsible for building the gui
from turtle import width
from trsh_gui.main_window import MainWindow
from trsh_gui.console_widget import ConsoleWidget
from PyQt6.QtWidgets import QVBoxLayout

def create_main_window():
    return MainWindow()
    
def create_console_widget():
    return ConsoleWidget()

def create_layout():
    return QVBoxLayout()

def assemble_gui():
    main_window = create_main_window()
    console_widget = create_console_widget()
    main_layout = create_layout()
    
    main_layout.addWidget(console_widget)

    main_window.setLayout(main_layout)
    return main_window
