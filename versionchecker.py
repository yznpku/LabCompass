from PyQt5.QtCore import QObject, QTimer, QThread, pyqtSignal
import datetime
import json
import urllib.request

class VersionChecker(QObject):
  requestVersionCheck = pyqtSignal()

  def __init__(self, Global, options):
    super().__init__()
    self.labNotesDate = (0, 0, 0)
    self.Global = Global
    self.options = options

    self.worker = VersionCheckerWorker()
    self.requestVersionCheck.connect(self.worker.run)
    self.worker.versionStringReceived.connect(self.onVersionCheckSuccess)

    self.timer = QTimer()
    self.timer.setInterval(1000)
    self.timer.start()
    self.timer.timeout.connect(self.compareLabNotesDate)
    self.timer.timeout.connect(self.scheduleVersionCheck)

  def setLabNotesDate(self, date):
    self.labNotesDate = date
    self.compareLabNotesDate()

  def compareLabNotesDate(self):
    today = datetime.datetime.utcnow()
    today = (today.year, today.month, today.day)
    self.Global.setProperty('labNotesOutDated', today != self.labNotesDate)

  def scheduleVersionCheck(self):
    now = datetime.datetime.now().timestamp()
    if now - self.options['lastVersionCheckAttempt'] > 300 and now - self.options['lastVersionCheckSuccess'] > 43200:
      self.options['lastVersionCheckAttempt'] = now
      self.requestVersionCheck.emit()

  def onVersionCheckSuccess(self, latest):
    now = datetime.datetime.now().timestamp()
    self.options['lastVersionCheckSuccess'] = now
    self.options['latestVersion'] = latest
    self.Global.setProperty('latestVersion', latest)


class VersionCheckerWorker(QObject):
  versionStringReceived = pyqtSignal(str)

  def __init__(self):
    super().__init__()
    self.thread = QThread()
    self.moveToThread(self.thread)
    self.thread.start()

  def run(self):
    try:
      o = json.loads(urllib.request.urlopen('https://api.github.com/repos/yznpku/LabCompass/releases/latest').read())
      self.versionStringReceived.emit(o['tag_name'])
    except Exception:
      pass

