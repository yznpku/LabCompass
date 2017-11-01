from PyQt5.QtCore import Qt, pyqtSlot

from window.template import TransparentWindow

class CompassWindow(TransparentWindow):
  def __init__(self, engine, **kwargs):
    super().__init__(engine, 'ui/Compass.qml', **kwargs)

  @pyqtSlot(int, list, list, list)
  def updateRoom(self, roomId, exitDirections, contentDirections, contents):
    self.rootObject().setProperty('exitDirectionModel', exitDirections)
    self.rootObject().setProperty('contentDirectionModel', contentDirections)
    self.rootObject().setProperty('contentModel', contents)

  @pyqtSlot(str)
  def markPlan(self, planDirection):
    self.rootObject().setProperty('planDirection', planDirection)

  def restartTimer(self):
    self.rootObject().restartTimer()

  def stopTimer(self):
    self.rootObject().stopTimer()

  def closeTimer(self):
    self.rootObject().closeTimer()
