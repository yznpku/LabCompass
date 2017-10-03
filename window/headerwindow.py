from window.template import OpaqueWindow

class HeaderWindow(OpaqueWindow):
  def __init__(self, engine, **kwargs):
    super().__init__(engine, 'qml/Header.qml', **kwargs)
    self.rootObject().drag.connect(lambda x, y: self.move(self.x() + x, self.y() + y))
