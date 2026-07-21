import sys
from PyQt6.QtWidgets import QApplication, QLabel, QMainWindow

class DropZone(QMainWindow):
    def __init__(self):
        super().__init__()
        self.setWindowTitle("File Path Saver")
        self.resize(400, 200)
        self.setAcceptDrops(True)
        
        self.label = QLabel("Drop a file here to save its path", self)
        self.label.setStyleSheet("font-size: 14px; padding: 20px;")
        self.setCentralWidget(self.label)

    def dragEnterEvent(self, event):
        if event.mimeData().hasUrls():
            event.acceptProposedAction()

    def dropEvent(self, event):
        urls = event.mimeData().urls()
        if not urls:
            return
            
        py_path = urls[0].toLocalFile() 
        
        with open("save.txt", "w", encoding="utf-8") as f:
            f.write(py_path)
            
        self.label.setText(f"Wiped save.txt & saved new path:\n{py_path}")
        print(f"Updated save.txt with: {py_path}")

app = QApplication(sys.argv)
demo = DropZone()
demo.show()
sys.argv = app.exec()
