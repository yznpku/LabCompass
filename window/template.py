from PyQt5.QtCore import Qt, QUrl, pyqtSignal, pyqtSlot
from PyQt5.QtWidgets import QWidget
from PyQt5.QtQuickWidgets import QQuickWidget

class Window(QQuickWidget):
  def __init__(self, engine, qmlPath, **kwargs):
    super().__init__(engine, None)
    self.qmlPath = qmlPath
    self.setClearColor(Qt.transparent)
    self.setAttribute(Qt.WA_NoSystemBackground)
    self.setAttribute(Qt.WA_TranslucentBackground)
    self.setAttribute(Qt.WA_TransparentForMouseEvents, 'transparent' in kwargs and kwargs['transparent'])
    if 'frameless' in kwargs and kwargs['frameless']:
      self.setWindowFlags(Qt.Tool | Qt.WindowDoesNotAcceptFocus | Qt.WindowStaysOnTopHint | Qt.FramelessWindowHint)
    else:
      self.setWindowFlags(Qt.Tool | Qt.WindowDoesNotAcceptFocus | Qt.WindowStaysOnTopHint)
    self.setSource(QUrl(qmlPath))

    if 'parent' in kwargs:
      self.parentWindow = kwargs['parent']
      self.offset = kwargs['offset']
      self.parentWindow.quickWindow().xChanged.connect(self.repositionToParent)
      self.parentWindow.quickWindow().yChanged.connect(self.repositionToParent)
      self.quickWindow().visibleChanged.connect(self.repositionToParent)
    else:
      self.move(300, 100)

  @pyqtSlot()
  def repositionToParent(self):
    self.move(self.parentWindow.quickWindow().x() + self.offset[0], self.parentWindow.quickWindow().y() + self.offset[1])


class TransparentWindow(Window):
  def __init__(self, engine, qmlPath, **kwargs):
    super().__init__(engine, qmlPath, transparent=True, frameless=True, **kwargs)

class OpaqueWindow(Window):
  def __init__(self, engine, qmlPath, **kwargs):
    super().__init__(engine, qmlPath, transparent=False, frameless=True, **kwargs)
