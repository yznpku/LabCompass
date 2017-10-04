from window.template import OpaqueWindow
from labanalyzer import LabAnalyzer

class PlannerWindow(OpaqueWindow):
  trials = [
    {'x': 242, 'y': 129, 'trial': True},
    {'x': 519, 'y': 129, 'trial': True},
    {'x': 794, 'y': 129, 'trial': True}
  ]

  def __init__(self, engine, labMap, **kwargs):
    super().__init__(engine, 'qml/Planner.qml', **kwargs)
    self.rootObject().move.connect(self.planMove)
    self.rootObject().back.connect(self.planBack)
    self.rootObject().reset.connect(self.planReset)
    self.labMap = labMap
    self.analyzer = LabAnalyzer()
    self.plan = [0]

  def showEvent(self, event):
    self.roomModel = [{'x': 0, 'y': 0, 'invalid': True} for i in range(len(self.labMap.rooms))]
    self.analyzeMap()
    for i, room in enumerate(self.labMap.rooms):
      self.roomModel[i]['contents'] = room['contents']
    self.rootObject().setProperty('roomModel', self.roomModel)

    self.linkModel = []
    for frm, room in enumerate(self.labMap.rooms):
      for to in room['exits']:
        if frm < to and 'invalid' not in self.roomModel[frm] and 'invalid' not in self.roomModel[to]:
          self.linkModel.append({
            'x1': self.roomModel[frm]['x'],
            'y1': self.roomModel[frm]['y'],
            'x2': self.roomModel[to]['x'],
            'y2': self.roomModel[to]['y'],
            'secret': room['exits'][to] == 'C'
          })
    self.rootObject().setProperty('linkModel', self.linkModel)

  def analyzeMap(self):
    self.analyzer.loadRooms(self.labMap.rooms)
    self.sections = self.analyzer.divideIntoSections()

    for i, section in enumerate(self.sections):
      preset = self.analyzer.findPreset(i, section)
      if preset:
        for i, coords in enumerate(preset):
          self.roomModel[section[0] + i + 1] = {'x': coords[0], 'y': coords[1]}

    for i in range(3):
      self.roomModel[self.sections[i][-1]] = self.trials[i]

  def planBack(self):
    plan = self.labMap.plan
    if len(plan) > 1:
      self.updatePlan(plan[:-1])

  def planMove(self, moveTo):
    plan = self.labMap.plan
    current = plan[-1]
    if moveTo in self.labMap.rooms[current]['exits']:
      plan.append(moveTo)
      self.updatePlan(plan)

  def planReset(self):
    self.updatePlan([0])

  def updatePlan(self, plan):
    self.labMap.plan = plan
    self.rootObject().setProperty('plan', plan[1:])

    planSet = set(plan[1:])
    rooms = len(planSet) - sum(self.labMap.rooms[i]['name'] == 'Aspirant\'s Trial' for i in planSet)
    length = len(plan) - 1
    argus = sum('argus' in self.labMap.rooms[i]['contents'] for i in planSet)
    gps = sum('gauntlet' in self.labMap.rooms[i]['contents'] for i in planSet) + sum('puzzle' in self.labMap.rooms[i]['contents'] for i in planSet)
    darkshrines = sum('darkshrine' in self.labMap.rooms[i]['contents'] for i in planSet)
    silverKeys = sum('silver-key' in self.labMap.rooms[i]['contents'] for i in planSet)
    silverDoors = sum('silver-door' in self.labMap.rooms[i]['contents'] for i in planSet)

    self.rootObject().setProperty('planRooms', rooms)
    self.rootObject().setProperty('planLength', length)
    self.rootObject().setProperty('planArgus', argus)
    self.rootObject().setProperty('planGPs', gps)
    self.rootObject().setProperty('planDarkshrines', darkshrines)
    self.rootObject().setProperty('planSilverKeys', silverKeys)
    self.rootObject().setProperty('planSilverDoors', silverDoors)
