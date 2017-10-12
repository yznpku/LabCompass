from window.template import OpaqueWindow

class PuzzleWindow(OpaqueWindow):
  def __init__(self, engine, **kwargs):
    super().__init__(engine, 'qml/Puzzle.qml', **kwargs)
    self.Global.puzzleWindowOpenChanged.connect(self.onWindowOpenChanged)

  def onWindowOpenChanged(self):
    isOpen = self.Global.property('puzzleWindowOpen')
    self.setVisible(isOpen)
    self.rootObject().setProperty('switchModel', 0)
    self.rootObject().setProperty('guideModel', 0)
