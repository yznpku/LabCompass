from window.template import OpaqueWindow

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
    self.plan = [0]
    self.Global.plannerWindowOpenChanged.connect(self.onWindowOpenChanged)
    self.refreshLayout()

  def onWindowOpenChanged(self):
    isOpen = self.Global.property('plannerWindowOpen')
    self.setVisible(isOpen)

  def refreshLayout(self):
    self.planReset()

    self.roomModel = self.labMap.rooms
    self.rootObject().setProperty('roomModel', self.roomModel)

    self.linkModel = []
    for frm, room in enumerate(self.labMap.rooms):
      for to, direction in room['exits']:
        if frm < to and 'invalid' not in self.roomModel[frm] and 'invalid' not in self.roomModel[to]:
          self.linkModel.append({
            'x1': self.roomModel[frm]['x'],
            'y1': self.roomModel[frm]['y'],
            'x2': self.roomModel[to]['x'],
            'y2': self.roomModel[to]['y'],
            'secret': direction == 'C'
          })
    self.rootObject().setProperty('linkModel', self.linkModel)
    self.rootObject().setProperty('goldenDoorModel', self.labMap.data['golden-door'] if 'golden-door' in self.labMap.data else [])
    self.rootObject().setProperty('labNoteTitle', self.labMap.data['date'] if 'date' in self.labMap.data else '')

  def planBack(self):
    plan = self.labMap.plan
    if len(plan) > 1:
      self.updatePlan(plan[:-1])

  def planMove(self, moveTo):
    plan = self.labMap.plan
    current = plan[-1]
    if any(exit[0] == moveTo for exit in self.labMap.rooms[current]['exits']):
      plan.append(moveTo)
      self.updatePlan(plan)

  def planReset(self):
    self.updatePlan([0])

  def updatePlan(self, plan):
    self.labMap.plan = plan
    self.labMap.currentPlanIndex = 0
    self.rootObject().setProperty('plan', plan[1:])

    planSet = set(plan[1:])
    rooms = len(planSet) - sum(self.labMap.rooms[i]['name'] == 'Aspirant\'s Trial' for i in planSet)
    length = len(plan) - 1
    argus = sum('argus' in self.labMap.rooms[i]['contents'] for i in planSet)
    gps = sum(sum(gp in self.labMap.rooms[i]['contents'] for gp in ['Switch puzzle', 'Floor puzzle', 'Escort gauntlet', 'Trap gauntlet']) for i in planSet)
    darkshrines = sum('darkshrine' in self.labMap.rooms[i]['contents'] for i in planSet)

    self.rootObject().setProperty('planRooms', rooms)
    self.rootObject().setProperty('planLength', length)
    self.rootObject().setProperty('planArgus', argus)
    self.rootObject().setProperty('planGPs', gps)
    self.rootObject().setProperty('planDarkshrines', darkshrines)
