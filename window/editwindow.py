from window.template import OpaqueWindow

class EditWindow(OpaqueWindow):
  def __init__(self, engine, **kwargs):
    super().__init__(engine, 'qml/Edit.qml', **kwargs)
