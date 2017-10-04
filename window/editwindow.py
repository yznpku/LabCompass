from window.template import OpaqueWindow

class EditWindow(OpaqueWindow):
  def __init__(self, engine, labMap, **kwargs):
    super().__init__(engine, 'qml/Edit.qml', **kwargs)
    self.labMap = labMap
    self.rootObject().exitDirection.connect(labMap.inputExitDirection)
    self.rootObject().contentDirection.connect(labMap.inputContentDirection)
    self.rootObject().content.connect(labMap.inputContent)
    self.rootObject().clearMap.connect(labMap.createNewLab)
    self.rootObject().iterateNext.connect(labMap.iterateNext)
    self.rootObject().save.connect(labMap.saveToFile)
