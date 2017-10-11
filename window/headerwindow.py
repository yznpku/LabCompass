from PyQt5.QtCore import QCoreApplication, pyqtSignal
from window.template import OpaqueWindow

class HeaderWindow(OpaqueWindow):
  onMoved = pyqtSignal(int, int)

  def __init__(self, engine, **kwargs):
    super().__init__(engine, 'qml/Header.qml', **kwargs)
    self.rootObject().drag.connect(self.drag)
    self.rootObject().exit.connect(lambda: QCoreApplication.instance().exit())

  def drag(self, x, y):
    self.move(self.x() + x, self.y() + y)
    self.onMoved.emit(self.x(), self.y())
