import json
import pprint
import string
from PyQt5.QtCore import Qt, QObject, pyqtSignal

class LabMap(QObject):
  markPlan = pyqtSignal(str)
  layoutChanged = pyqtSignal()
  roomChanged = pyqtSignal(int, list, list, list)

  def __init__(self):
    super().__init__()
    self.createNewLab()

  def createNewLab(self):
    self.data = {}
    self.rooms = []
    self.plan = [0]
    self.currentPlanIndex = 0
    self.currentRoom = -1
    self.previousRoom = -1
    plaza = {'name': 'Aspirant\'s Plaza',
             'contents': [],
             'content_directions': [],
             'x': -100,
             'y': 128,
             'exits': []}
    self.rooms.append(plaza)
    self.layoutChanged.emit()

  def loadFromFile(self, difficulty):
    self.createNewLab()
    o = {}
    try:
      with open('lab-notes-%s.json' % difficulty.lower()) as file:
        o = json.loads(file.read())
    except Exception:
      pass
    self.data = {**o}
    if 'rooms' in o:
      plaza = {'name': 'Aspirant\'s Plaza',
               'contents': [],
               'content_directions': [],
               'x': -100,
               'y': 128,
               'exits': [(1, 'NW')]}
      mapping = {room['id']: i + 1 for i, room in enumerate(o['rooms'])}
      for room in o['rooms']:
        room['exits'] = [(mapping[room['exits'][k]], k) for k in room['exits']]
        room['name'] = string.capwords(room['name'])

      self.rooms = [plaza, *o['rooms']]

      for i, room in enumerate(self.rooms):
        for to, direction in room['exits']:
          if not any(exit[0] == i for exit in self.rooms[to]['exits']):
            self.rooms[to]['exits'].append((i, 'unknown'))

    self.layoutChanged.emit()

  def labStart(self):
    self.currentPlanIndex = 0
    self.currentRoom = 0
    self.previousRoom = -1
    self.sendUpdateSignal()
    self.print()

  def enterZone(self, zoneName):
    self.previousRoom = self.currentRoom
    if self.previousRoom == self.plan[self.currentPlanIndex] and self.currentPlanIndex < len(self.plan) - 1 and self.rooms[self.plan[self.currentPlanIndex + 1]]['name'] == zoneName:
      self.currentPlanIndex += 1
      self.currentRoom = self.plan[self.currentPlanIndex]
    else:
      for to, direction in self.rooms[self.previousRoom]['exits']:
        if self.rooms[to]['name'] == zoneName:
          self.currentRoom = to
          break

    self.sendUpdateSignal()
    self.print()

  def labExit(self):
    self.currentRoom = -1
    self.previousRoom = -1
    self.sendUpdateSignal()
    self.print()

  def print(self):
    print('current: %d' % self.currentRoom)
    print('previous: %d' % self.previousRoom)
    pprint.pprint(self.rooms)

  def sendUpdateSignal(self):
    if self.currentRoom in range(len(self.rooms)):
      self.roomChanged.emit(self.currentRoom,
                            [exit[1] for exit in self.rooms[self.currentRoom]['exits'] if exit[1] != 'unknown'],
                            self.rooms[self.currentRoom]['content_directions'],
                            self.rooms[self.currentRoom]['contents'])
    else:
      self.roomChanged.emit(self.currentRoom, [], [], [])

    if self.currentRoom == self.plan[self.currentPlanIndex] and self.currentPlanIndex < len(self.plan) - 1:
      for to, direction in self.rooms[self.currentRoom]['exits']:
        if to == self.plan[self.currentPlanIndex + 1]:
          self.markPlan.emit(direction)
          break
    else:
      self.markPlan.emit('')
