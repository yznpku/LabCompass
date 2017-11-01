from PyQt5.QtCore import QTimer
import datetime

class VersionChecker:

  def __init__(self, Global):
    self.labNotesDate = (0, 0, 0)
    self.Global = Global

    self.timer = QTimer()
    self.timer.setInterval(1000)
    self.timer.start()
    self.timer.timeout.connect(self.recheckLabNotesValidity)

  def setLabNotesDate(self, date):
    self.labNotesDate = date
    self.recheckLabNotesValidity()

  def recheckLabNotesValidity(self):
    today = datetime.datetime.utcnow()
    today = (today.year, today.month, today.day)
    self.Global.setProperty('labNotesOutDated', today != self.labNotesDate)
