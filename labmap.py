import json
import shutil
import string
from PyQt5.QtCore import Qt, QObject, QStandardPaths, pyqtSignal
from PyQt5.QtWidgets import QFileDialog
from labmapmodel import LabMapModel

class LabMap(QObject):
  markPlan = pyqtSignal(str)
  dateChanged = pyqtSignal(tuple)
  layoutChanged = pyqtSignal()
  currentRoomChanged = pyqtSignal(int)
  currentPlanIndexChanged = pyqtSignal(int)
  roomMapUpdated = pyqtSignal(int, list, list, list)

  def __init__(self, **kwargs):
    super().__init__()
    self.loadContentLocations()
    self.loadFromFile()

  def loadContentLocations(self):
    self.contentLocations = {}
    try:
      with open(self.contentLocationsFile) as file:
        self.contentLocations = json.loads(file.read())
    except Exception:
      pass

  def createNewLab(self):
    self.model = LabMapModel()
    self.layoutChanged.emit()

  def importLabNotes(self):
    downloadDirectory = QStandardPaths.standardLocations(QStandardPaths.DownloadLocation)[0] if len(QStandardPaths.standardLocations(QStandardPaths.DownloadLocation)) else ''
    file, _ = QFileDialog.getOpenFileName(None, 'Import Lab Notes', downloadDirectory, 'Lab Notes (*.json)')
    if file:
      shutil.copyfile(file, './lab-notes.json')
      self.loadFromFile()

  def loadFromFile(self):
    self.createNewLab()
    model = LabMapModel.loadFromFile('./lab-notes.json')
    if model:
      self.model = model
      self.dateChanged.emit(model.date())
      self.layoutChanged.emit()

  def labStart(self):
    self.model.currentPlanIndex = 0
    self.model.currentRoom = 0
    self.model.previousRoom = -1
    self.sendUpdateSignal()

  def enterZone(self, zoneName):
    self.model.previousRoom = self.model.currentRoom
    if self.model.previousRoom == self.model.plan[self.model.currentPlanIndex] \
        and self.model.currentPlanIndex < len(self.model.plan) - 1 \
        and self.model.rooms[self.model.plan[self.model.currentPlanIndex + 1]]['name'] == zoneName:
      self.model.currentPlanIndex += 1
      self.model.currentRoom = self.model.plan[self.model.currentPlanIndex]
    else:
      for to, direction in self.model.rooms[self.model.previousRoom]['exits']:
        if self.model.rooms[to]['name'] == zoneName:
          self.model.currentRoom = to
          break

    self.sendUpdateSignal()

  def labExit(self):
    self.model.currentRoom = -1
    self.model.previousRoom = -1
    self.sendUpdateSignal()

  def sendUpdateSignal(self):
    if self.model.currentRoom in range(len(self.model.rooms)):
      self.roomMapUpdated.emit(self.model.currentRoom,
                               [exit[1] for exit in self.model.rooms[self.model.currentRoom]['exits'] if exit[1] != 'unknown' and exit[1] != 'C'],
                               self.model.rooms[self.model.currentRoom]['content_directions'],
                               self.model.rooms[self.model.currentRoom]['contents'])
    else:
      self.roomMapUpdated.emit(self.model.currentRoom, [], [], [])

    if self.model.currentRoom == self.model.plan[self.model.currentPlanIndex] and self.model.currentPlanIndex < len(self.model.plan) - 1:
      for to, direction in self.model.rooms[self.model.currentRoom]['exits']:
        if to == self.model.plan[self.model.currentPlanIndex + 1]:
          self.markPlan.emit(direction)
          break
    else:
      self.markPlan.emit('')

    self.currentRoomChanged.emit(self.model.currentRoom)
    self.currentPlanIndexChanged.emit(self.model.currentPlanIndex)
