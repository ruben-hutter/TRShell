# reads external qss stylesheets
def read_style_sheet(style_sheet):
    with open(style_sheet, 'r') as file:
        return file.read()