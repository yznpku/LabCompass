from window.template import OpaqueWindow

class ToolbarWindow(OpaqueWindow):
  def __init__(self, engine, **kwargs):
    super().__init__(engine, 'qml/Toolbar.qml', **kwargs)
