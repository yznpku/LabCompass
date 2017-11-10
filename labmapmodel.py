import json
import shutil
import string
from PyQt5.QtCore import Qt, QObject, QStandardPaths, pyqtSignal
from PyQt5.QtWidgets import QFileDialog

class LabMapModel:
  def __init__(self):
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

  @staticmethod
  def loadFromFile(fileName):
    model = LabMapModel()
    try:
      o = {}
      with open(fileName) as file:
        o = json.loads(file.read())

      model.data = {**o}
      del model.data['rooms']
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

        model.rooms = [plaza, *o['rooms']]

        for i, room in enumerate(model.rooms):
          for to, direction in room['exits']:
            if not any(exit[0] == i for exit in model.rooms[to]['exits']):
              model.rooms[to]['exits'].append((i, 'unknown'))

        trials = [room for room in model.rooms if room['name'] == 'Aspirant\'s Trial']
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

        model.data['golden-door'] = []
        for i, room in enumerate(model.rooms):
          if 'golden-door' in room['contents']:
            for to, direction in room['exits']:
              if direction != 'C' \
                  and to > i \
                  and not model.isSideRoom(to):
                model.data['golden-door'].append([i, to])
      return model
    except Exception:
      return None

  def date(self):
    if 'date' in self.data:
      date = self.data['date'].split('-')
      if len(date) == 3:
        return tuple(map(int, date))
    return (0, 0, 0)

  def isSideRoom(self, index):
    exits = sum(direction != 'C' for to, direction in self.rooms[index]['exits'])
    return exits == 1
