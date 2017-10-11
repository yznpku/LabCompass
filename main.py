import sys

from PyQt5.QtCore import Qt, QUrl, QTimer
from PyQt5.QtWidgets import QApplication
from PyQt5.QtGui import QFont
from PyQt5.QtQml import qmlRegisterSingletonType, QQmlApplicationEngine
from PyQt5.QtQuick import QQuickView
from PyQt5.QtQuickWidgets import QQuickWidget

from window import TransparentWindow, CompassWindow, HeaderWindow, PlannerWindow, ToolbarWindow
from logwatcher import LogWatcher
from labnoteupdater import LabNoteUpdater
from labmap import LabMap
from connect import connect

sys_argv = sys.argv
sys_argv += ['--style', 'material']
app = QApplication(sys_argv)

font = QFont('consolas')
font.setPointSize(10)
QApplication.setFont(font)

engine = QQmlApplicationEngine()
qmlRegisterSingletonType(QUrl.fromLocalFile('qml/Global.qml'), 'com.labcompass', 1, 0, 'Global')
engine.load(QUrl.fromLocalFile('qml/GlobalAccessor.qml'))
Global = engine.rootObjects()[0].property('o')

dummy = TransparentWindow(engine, 'qml/Dummy.qml')
dummy.show()

labMap = LabMap()

logWatcher = LogWatcher()
QTimer.singleShot(0, logWatcher.start)

labNoteUpdater = LabNoteUpdater()

header = HeaderWindow(engine, initialPos=(500, 200))
header.show()

compass = CompassWindow(engine, parent=header, offset=(-10, 32))
compass.show()

toolbar = ToolbarWindow(engine, parent=header, offset=(0, 168))
toolbar.show()

plannerWindow = PlannerWindow(engine, labMap)

connect({
  logWatcher.labStart: [labMap.labStart, compass.restartTimer, (lambda: Global.setProperty('inLab', True))],
  logWatcher.zoneChange: [labMap.enterZone],
  logWatcher.labFinish: [compass.stopTimer],
  logWatcher.labExit: [labMap.labExit, compass.closeTimer, (lambda: Global.setProperty('inLab', False))],
  labMap.layoutChanged: [plannerWindow.refreshLayout],
  labMap.roomChanged: [compass.updateRoom],
  labMap.markPlan: [compass.markPlan],
  labNoteUpdater.runningChanged: [(lambda running: Global.setProperty('labNoteUpdaterRunning', running))],
  labNoteUpdater.success: [labMap.loadFromFile],
  plannerWindow.rootObject().updateLabNotes: [labNoteUpdater.fetchLabNotes]
})


app.exec()
