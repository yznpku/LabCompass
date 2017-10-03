import codecs
import time
import re

from PyQt5.QtCore import Qt, pyqtSignal, pyqtSlot, QObject, QThread

START_LINES = ['Izaro: Ascend with precision.', 'Izaro: The Goddess is watching.', 'Izaro: Justice will prevail.']
FINISH_LINES = ['Izaro: I die for the Empire!', 'Izaro: Delight in your gilded dungeon, ascendant.', 'Izaro: Your destination is more dangerous than the journey, ascendant.', 'Izaro: Triumphant at last!', 'Izaro: You are free!', 'Izaro: The trap of tyranny is inescapable.']
SECTION_COMPLETE_LINES = ['Izaro: By the Goddess! What ambition!', 'Izaro: Such resilience!', 'Izaro: You are inexhaustible!', 'Izaro: You were born for this!']
ZONE_PREFIX = ['Estate', 'Domain', 'Basilica', 'Mansion', 'Sepulchre', 'Sanitorium']
ZONE_SUFFIX = ['Walkways', 'Path', 'Crossing', 'Annex', 'Halls', 'Passage', 'Enclosure', 'Atrium']
DIRECTION = {'N': [0, -1], 'NE': [0.71, -0.71], 'E': [1, 0], 'SE': [0.71, 0.71], 'S': [0, 1], 'SW': [-0.71, 0.71], 'W': [-1, 0], 'NW': [-0.71, -0.71]}
ZONE_REGEX = re.compile(r'^: You have entered (.*?)\.$')
LOG_REGEX = re.compile(r'^\d+/\d+/\d+ \d+:\d+:\d+.*?\[.*?\] (.*)$')

class LogWatcher(QObject):
  labStart = pyqtSignal()
  labFinish = pyqtSignal()
  labExit = pyqtSignal()
  sectionComplete = pyqtSignal()
  zoneChange = pyqtSignal(str)

  def __init__(self):
    super().__init__()
    self.thread = QThread()
    self.moveToThread(self.thread)
    self.thread.start()

  @pyqtSlot()
  def start(self):
    with codecs.open('C:/Program Files (x86)/Steam/steamapps/common/Path of Exile/logs/Client.txt', 'r', encoding='utf-8') as log:
      while log.readline():
        pass
      print('log watcher ready')
      while True:
        where = log.tell()
        line = log.readline()
        if not line:
          time.sleep(1)
          log.seek(where)
        else:
          m = re.match(LOG_REGEX, line)
          if m:
            log_content = m.group(1).strip()
            m1 = re.match(ZONE_REGEX, log_content)
            if m1:
              zone = m1.group(1)
              affixes = zone.split(' ')
              if (affixes[0] in ZONE_PREFIX and affixes[1] in ZONE_SUFFIX) or zone == 'Aspirant\'s Trial':
                self.zoneChange.emit(m1.group(1))
              else:
                self.labExit.emit()
            elif log_content in START_LINES:
              self.labStart.emit()
            elif log_content in FINISH_LINES:
              self.labFinish.emit()
            elif log_content in SECTION_COMPLETE_LINES:
              self.sectionComplete.emit()
