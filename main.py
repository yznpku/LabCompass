import sys

from PyQt5.QtCore import Qt, QUrl, QTimer
from PyQt5.QtWidgets import QApplication, QMessageBox
from PyQt5.QtGui import QFont
from PyQt5.QtQml import qmlRegisterSingletonType, QQmlApplicationEngine
from PyQt5.QtQuick import QQuickView
from PyQt5.QtQuickWidgets import QQuickWidget

from window import TransparentWindow, CompassWindow, HeaderWindow, PlannerWindow, ToolbarWindow
from logwatcher import LogWatcher
from labnoteupdater import LabNoteUpdater
from labmap import LabMap
from connect import connect
from options import Options
import clientutils

sys_argv = sys.argv
sys_argv += ['--style', 'material']
app = QApplication(sys_argv)

options = Options()
if not clientutils.verifyClientPath(options['poeClientPath']):
  options['poeClientPath'] = clientutils.getClientPath()

font = QFont('consolas')
font.setPointSize(10)
QApplication.setFont(font)

engine = QQmlApplicationEngine()
qmlRegisterSingletonType(QUrl.fromLocalFile('qml/Global.qml'), 'com.labcompass', 1, 0, 'Global')
engine.load(QUrl.fromLocalFile('qml/GlobalAccessor.qml'))
Global = engine.rootObjects()[0].property('o')

dummy = TransparentWindow(engine, 'qml/Dummy.qml')
dummy.show()

labMap = LabMap(difficulty=options['difficulty'])

logWatcher = LogWatcher(options['poeClientPath'])
QTimer.singleShot(1, logWatcher.start)

labNoteUpdater = LabNoteUpdater()

header = HeaderWindow(engine, initialPos=options['mainWindowPosition'])
header.show()

compass = CompassWindow(engine, parent=header, offset=(-48, 26))
compass.show()

toolbar = ToolbarWindow(engine, parent=header, offset=(124, 28))
toolbar.show()

plannerWindow = PlannerWindow(engine, labMap)

connect({
  logWatcher.labStart: [labMap.labStart, compass.restartTimer, (lambda: Global.setProperty('inLab', True))],
  logWatcher.zoneChange: [labMap.enterZone],
  logWatcher.labFinish: [compass.stopTimer],
  logWatcher.labExit: [labMap.labExit, compass.closeTimer, (lambda: Global.setProperty('inLab', False))],
  logWatcher.fail: [(lambda: QMessageBox.information(None, 'LabCompass', 'Cannot locate POE client. Please make sure the client is running, and restart LabCompass.'))],
  labMap.layoutChanged: [plannerWindow.refreshLayout],
  labMap.roomChanged: [compass.updateRoom],
  labMap.markPlan: [compass.markPlan],
  labNoteUpdater.runningChanged: [(lambda running: Global.setProperty('labNoteUpdaterRunning', running))],
  labNoteUpdater.success: [labMap.loadFromFile],
  plannerWindow.rootObject().updateLabNotes: [labNoteUpdater.fetchLabNotes],
  plannerWindow.rootObject().switchToDifficulty: [labMap.loadFromFile],
  header.onMoved: [(lambda x, y: options.update({'mainWindowPosition': [x, y]}))]
})

app.exec()
options.saveToFile()
