import json
import pprint
from PyQt5.QtCore import Qt, QObject, pyqtSignal

class LabMap(QObject):
  markPlan = pyqtSignal(str)
  roomChanged = pyqtSignal(int, list, list, list)
  labNoteFile = 'lab-notes.json'

  def __init__(self):
    super().__init__()
    self.directionBuffer = []
    self.sectionCompleted = False
    self.editMode = False
    self.createNewLab()
    self.loadFromFile()

  def createNewLab(self):
    self.rooms = []
    self.plan = [0]
    self.currentPlanIndex = 0
    self.currentRoom = -1
    self.previousRoom = -1
    self.sectionStart = 0
    plaza = {'name': 'Aspirant\'s Plaza',
             'contents': [],
             'content_directions': [],
             'exits': {}}
    self.rooms.append(plaza)

  def loadFromFile(self):
    o = {}
    try:
      with open(self.labNoteFile) as file:
        o = json.loads(file.read())
    except Exception:
      pass
    if 'rooms' in o:
      plaza = {'name': 'Aspirant\'s Plaza',
              'contents': [],
              'content_directions': [],
              'x': -100,
              'y': 128,
              'exits': {1: 'NW'}}
      mapping = {room['id']: i + 1 for i, room in enumerate(o['rooms'])}
      for room in o['rooms']:
        room['exits'] = {mapping[k]:room['exits'][k] for k in room['exits']}

      self.rooms = [plaza, *o['rooms']]

      for i, room in enumerate(self.rooms):
        for exit in room['exits']:
          if not i in self.rooms[exit]['exits']:
            self.rooms[exit]['exits'][i] = 'unknown'

  def labStart(self):
    self.currentPlanIndex = 0
    self.currentRoom = 0
    self.previousRoom = -1
    self.sectionStart = 0
    self.sendUpdateSignal()
    self.print()

  def enterZone(self, zoneName):
    self.previousRoom = self.currentRoom
    if self.editMode:
      for i in range(self.sectionStart, len(self.rooms)):
        if self.rooms[i]['name'] == zoneName:
          self.currentRoom = i
          break
      else:
        self.newZone(zoneName)

    else:
      if self.previousRoom == self.plan[self.currentPlanIndex] and self.currentPlanIndex < len(self.plan) - 1 and self.rooms[self.plan[self.currentPlanIndex + 1]]['name'] == zoneName:
        self.currentPlanIndex += 1
        self.currentRoom = self.plan[self.currentPlanIndex]
      else:
        for i in self.rooms[self.previousRoom]['exits']:
          if self.rooms[i]['name'] == zoneName:
            self.currentRoom = i
            break
    if self.sectionCompleted:
      self.sectionStart = self.currentRoom
      self.sectionCompleted = False
    self.sendUpdateSignal()
    self.print()

  def sectionComplete(self):
    self.sectionCompleted = True

  def labExit(self):
    self.currentRoom = -1
    self.previousRoom = -1
    self.sendUpdateSignal()
    self.print()

  def iterateNext(self):
    for i in range(self.currentRoom + 1, len(self.rooms)):
      if self.rooms[i]['name'] == self.rooms[self.currentRoom]['name']:
        self.currentRoom = i
        break
    else:
      self.newZone(self.rooms[self.currentRoom]['name'])
    self.sendUpdateSignal()
    self.print()

  def newZone(self, zoneName):
    self.currentRoom = len(self.rooms)
    newRoom = {'name': zoneName,
               'contents': [],
               'content_directions': [],
               'exits': {}}
    self.rooms.append(newRoom)

  def connectZones(self, leavingDirection, enteringDirection):
    if self.previousRoom in range(len(self.rooms)) and self.currentRoom in range(len(self.rooms)):
      self.rooms[self.previousRoom]['exits'][self.currentRoom] = leavingDirection
      self.rooms[self.currentRoom]['exits'][self.previousRoom] = enteringDirection
    self.sendUpdateSignal()
    self.print()

  def inputExitDirection(self, direction):
    self.directionBuffer.append(direction)
    if len(self.directionBuffer) == 2:
      self.connectZones(*self.directionBuffer)
      self.directionBuffer = []

  def inputContentDirection(self, direction):
    if direction in self.rooms[self.currentRoom]['content_directions']:
      self.rooms[self.currentRoom]['content_directions'].remove(direction)
    else:
      self.rooms[self.currentRoom]['content_directions'].append(direction)
    self.sendUpdateSignal()
    self.print()

  def inputContent(self, name):
    if name == 'gauntlet' or name == 'puzzle':
      if sum(name == x for x in self.rooms[self.currentRoom]['contents']) == 2:
        while name in self.rooms[self.currentRoom]['contents']:
          self.rooms[self.currentRoom]['contents'].remove(name)
      else:
        self.rooms[self.currentRoom]['contents'].append(name)
    else:
      if name in self.rooms[self.currentRoom]['contents']:
        self.rooms[self.currentRoom]['contents'].remove(name)
      else:
        self.rooms[self.currentRoom]['contents'].append(name)
    self.sendUpdateSignal()
    self.print()

  def setEditMode(self, editMode):
    self.editMode = editMode

  def saveToFile(self):
    with open(self.labNoteFile, 'w') as file:
      file.write(json.dumps({'rooms': self.rooms}))

  def print(self):
    print('current: %d' % self.currentRoom)
    print('previous: %d' % self.previousRoom)
    print('section: %d' % self.sectionStart)
    pprint.pprint(self.rooms)

  def sendUpdateSignal(self):
    if self.currentRoom in range(len(self.rooms)):
      self.roomChanged.emit(self.currentRoom,
                            list(self.rooms[self.currentRoom]['exits'].values()),
                            self.rooms[self.currentRoom]['content_directions'],
                            self.rooms[self.currentRoom]['contents'])
    else:
      self.roomChanged.emit(self.currentRoom, [], [], [])

    if self.currentRoom == self.plan[self.currentPlanIndex] and self.currentPlanIndex < len(self.plan) - 1:
      self.markPlan.emit(self.rooms[self.currentRoom]['exits'][self.plan[self.currentPlanIndex + 1]])
    else:
      self.markPlan.emit('')
