import re
import urllib.request
from lxml import html

from PyQt5.QtCore import Qt, pyqtSignal, pyqtSlot, QObject, QThread

class LabNoteUpdater(QObject):
  runningChanged = pyqtSignal(bool)
  success = pyqtSignal(str)
  failure = pyqtSignal()
  fileNamePattern = re.compile(r'(.*?)-(\d{4})-(\d{2})-(\d{2})')

  def __init__(self):
    super().__init__()
    self.thread = QThread()
    self.moveToThread(self.thread)
    self.thread.start()

  @pyqtSlot(str)
  def fetchLabNotes(self, difficulty):
    self.runningChanged.emit(True)

    for item in self.fetchLabNoteList():
      m = re.match(self.fileNamePattern, item[0])
      noteDifficulty, yyyy, mm, dd = m.groups()
      if noteDifficulty.lower() == difficulty.lower():
        request = urllib.request.Request('https://pastebin.com/raw' + item[1],
                                         headers={'User-Agent': 'Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/60.0.3112.113 Safari/537.36'})
        try:
          response = urllib.request.urlopen(request).read()
          with open('lab-notes-%s.json' % noteDifficulty.lower(), 'wb') as file:
            file.write(response)
          self.success.emit(difficulty)
          break
        except Exception as e:
          pass
    else:
      self.failure.emit()

    self.runningChanged.emit(False)

  @pyqtSlot()
  def fetchLabNoteList(self):
    request = urllib.request.Request('https://pastebin.com/u/JP_dev',
                                     headers={'User-Agent': 'Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/60.0.3112.113 Safari/537.36'})
    try:
      response = urllib.request.urlopen(request).read()
      tree = html.fromstring(response)
      l = tree.xpath('//table[@class="maintable"]/tr/td[1]/a')
      return [(e.text, e.attrib['href']) for e in l]
    except Exception as e:
      return []
