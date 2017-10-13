import json
import string
from PyQt5.QtCore import Qt, QObject, pyqtSignal

class LabMap(QObject):
  markPlan = pyqtSignal(str)
  layoutChanged = pyqtSignal()
  currentRoomChanged = pyqtSignal(int)
  currentPlanIndexChanged = pyqtSignal(int)
  roomMapUpdated = pyqtSignal(int, list, list, list)

  def __init__(self, **kwargs):
    super().__init__()
    if 'difficulty' in kwargs:
      self.loadFromFile(kwargs['difficulty'])
    else:
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

    try:
      o = {}
      with open('lab-notes-%s.json' % difficulty.lower()) as file:
        o = json.loads(file.read())

      self.data = {**o}
      del self.data['rooms']
      if 'rooms' in o:
        plaza = {'name': 'Aspirant\'s Plaza',
                 'contents': [],
                 'content_directions': [],
                 'x': -100,
                 'y': 128,
                 'exits': [(1, 'NW')]}
        mapping = {room['id']: i + 1 for i, room in enumerate(o['rooms'])}
        for room in o['rooms']:
          if 'secret_passage' in room and mapping[room['exits']['C']] < mapping[room['id']]:
            room['secret_passage'] = 'From Room %d' % mapping[room['exits']['C']]
          room['exits'] = [(mapping[room['exits'][k]], k) for k in room['exits']]
          room['name'] = string.capwords(room['name'])
          room['x'] = int(room['x'])
          room['y'] = int(room['y'])

        self.rooms = [plaza, *o['rooms']]

        for i, room in enumerate(self.rooms):
          for to, direction in room['exits']:
            if not any(exit[0] == i for exit in self.rooms[to]['exits']):
              self.rooms[to]['exits'].append((i, 'unknown'))

        trials = [room for room in self.rooms if room['name'] == 'Aspirant\'s Trial']
        if len(trials) == 3:
          for trial in trials:
            trial['mechanics'] = []
            if 'weapon' in o:
              trial['weapon'] = o['weapon']
          if 'phase1' in o:
            trials[0]['mechanics'].append(o['phase1'])
          if 'phase2' in o:
            trials[1]['mechanics'].append(o['phase2'])
          if 'trap1' in o and o['trap1'] != 'NoTrap':
            trials[2]['mechanics'].append(o['trap1'])
          if 'trap2' in o and o['trap2'] != 'NoTrap':
            trials[2]['mechanics'].append(o['trap2'])

        self.data['golden-door'] = []
        for i, room in enumerate(self.rooms):
          if 'golden-door' in room['contents']:
            for to, direction in room['exits']:
              if direction != 'C' and to > i and 'golden-key' not in self.rooms[to]['contents']:
                self.data['golden-door'].append([i, to])
    except Exception:
      self.createNewLab()
      return

    self.layoutChanged.emit()

  def labStart(self):
    self.currentPlanIndex = 0
    self.currentRoom = 0
    self.previousRoom = -1
    self.sendUpdateSignal()

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

  def labExit(self):
    self.currentRoom = -1
    self.previousRoom = -1
    self.sendUpdateSignal()

  def sendUpdateSignal(self):
    if self.currentRoom in range(len(self.rooms)):
      self.roomMapUpdated.emit(self.currentRoom,
                               [exit[1] for exit in self.rooms[self.currentRoom]['exits'] if exit[1] != 'unknown' and exit[1] != 'C'],
                               self.rooms[self.currentRoom]['content_directions'],
                               self.rooms[self.currentRoom]['contents'])
    else:
      self.roomMapUpdated.emit(self.currentRoom, [], [], [])

    if self.currentRoom == self.plan[self.currentPlanIndex] and self.currentPlanIndex < len(self.plan) - 1:
      for to, direction in self.rooms[self.currentRoom]['exits']:
        if to == self.plan[self.currentPlanIndex + 1]:
          self.markPlan.emit(direction)
          break
    else:
      self.markPlan.emit('')

    self.currentRoomChanged.emit(self.currentRoom)
    self.currentPlanIndexChanged.emit(self.currentPlanIndex)
