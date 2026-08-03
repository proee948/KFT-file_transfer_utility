import sys
import os
import subprocess
import PyQt6.QtGui
import PyQt6.QtCore
from PyQt6.QtWidgets import (
    QApplication, 
    QMainWindow, 
    QWidget, 
    QVBoxLayout, 
    QPushButton, 
    QLabel
)

class start_ftp(QWidget):
    def __init__(self, parent=None):
        super().__init__(parent)
        self.main_window = parent
        
        layout = QVBoxLayout(self)
        self.dugme = QPushButton(text="start", parent=self)
        self.dugme.setFixedSize(60, 40)
        
        self.dugme.clicked.connect(self.execute_c_backend)
        layout.addWidget(self.dugme)
        
    def execute_c_backend(self):
        if not self.main_window.has_dropped_file:
            print("ERROR: cannot start. No file has been dragged into the window")
            self.main_window.label.setText("ERROR: drag a file here first before starting!")
            self.main_window.label.setStyleSheet("font-size: 14px; padding: 20px; color: red;")
            return

        if not os.path.exists("save.txt"):
            print("ERROR: save.txt missing from directory.")
            return

        print("Success: File verified. Executing './_name_' in background...")
        
        try:
            subprocess.Popen(["./host"])
            print("Background process './host' successfully spawned.")
            
        except FileNotFoundError:
            print("ERROR: Could not find the executable binary './host' in this folder.")
        except Exception as e:
            print(f"System Error while spawning process: {e}")


class DropZone(QMainWindow):
    def __init__(self):
        super().__init__()
        self.setWindowTitle("file transfer GUI")
        self.resize(400, 300)
        self.setAcceptDrops(True)
        
        self.has_dropped_file = False
        
        container = QWidget()
        self.setCentralWidget(container)
        main_layout = QVBoxLayout(container)
        
        self.label = QLabel("Drop a file here to save its path", self)
        self.label.setStyleSheet("font-size: 14px; padding: 20px;")
        main_layout.addWidget(self.label)
        
        self.ftp_widget = start_ftp(parent=self)
        main_layout.addWidget(self.ftp_widget)

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
            
        self.has_dropped_file = True
        self.label.setStyleSheet("font-size: 14px; padding: 20px; color: green;")
        self.label.setText(f"ready to send\nsaved path:\n{py_path}")
        print(f"updated save.txt with: {py_path}")


if __name__ == "__main__":
    app = QApplication(sys.argv)
    demo = DropZone()
    demo.show()
    sys.exit(app.exec())
