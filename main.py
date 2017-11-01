import os
import sys

from PyQt5.QtCore import Qt, QDir, QUrl, QTimer
from PyQt5.QtWidgets import QApplication, QMessageBox
from PyQt5.QtGui import QFont, QFontDatabase
from PyQt5.QtQml import qmlRegisterSingletonType, QQmlApplicationEngine
from PyQt5.QtQuick import QQuickView
from PyQt5.QtQuickWidgets import QQuickWidget

from window import TransparentWindow, CompassWindow, HeaderWindow, PlannerWindow, ToolbarWindow, PuzzleWindow, OptionsWindow
from logwatcher import LogWatcher
from labmap import LabMap
from connect import connect
from options import Options
from versionchecker import VersionChecker
import clientutils

os.environ['QML_DISABLE_DISK_CACHE'] = '1'
sys_argv = sys.argv
sys_argv += ['--style', 'material']
app = QApplication(sys_argv)

options = Options()
if not clientutils.verifyClientPath(options['poeClientPath']):
  options['poeClientPath'] = clientutils.getClientPath()

QFontDatabase.addApplicationFont('Fontin-SmallCaps.ttf')
font = QFont('Fontin SmallCaps')
font.setPixelSize(16)
QApplication.setFont(font)

engine = QQmlApplicationEngine()
qmlRegisterSingletonType(QUrl.fromLocalFile('ui/Global.qml'), 'com.labcompass', 1, 0, 'Global')
engine.load(QUrl.fromLocalFile('ui/GlobalAccessor.qml'))
Global = engine.rootObjects()[0].property('o')

dummy = TransparentWindow(engine, 'ui/Dummy.qml')
dummy.show()

labMap = LabMap()

logWatcher = LogWatcher(options['poeClientPath'])
QTimer.singleShot(1, logWatcher.start)

versionChecker = VersionChecker(Global)
versionChecker.labNotesDate = labMap.getLabNotesDate()

header = HeaderWindow(engine, initialPos=options['mainWindowPosition'])
header.show()

compass = CompassWindow(engine, parent=header, offset=(-48, 26))
compass.show()

toolbar = ToolbarWindow(engine, parent=header, offset=(124, 28))
toolbar.show()

plannerWindow = PlannerWindow(engine, labMap)
puzzleWindow = PuzzleWindow(engine, parent=header, offset=(-122, 220))
optionsWindow = OptionsWindow(engine)

connect({
  logWatcher.labStart: [labMap.labStart, compass.restartTimer, (lambda: Global.setProperty('inLab', True))],
  logWatcher.zoneChange: [labMap.enterZone],
  logWatcher.labFinish: [compass.stopTimer],
  logWatcher.labExit: [labMap.labExit, compass.closeTimer, (lambda: Global.setProperty('inLab', False))],
  logWatcher.fail: [(lambda: QMessageBox.information(None, 'LabCompass', 'Cannot locate POE client. Please make sure the client is running, and restart LabCompass.'))],
  labMap.dateChanged: [versionChecker.setLabNotesDate],
  labMap.layoutChanged: [plannerWindow.refreshLayout],
  labMap.roomMapUpdated: [compass.updateRoom],
  labMap.markPlan: [compass.markPlan],
  labMap.currentRoomChanged: [(lambda x: Global.setProperty('currentRoom', x))],
  labMap.currentPlanIndexChanged: [(lambda x: Global.setProperty('currentPlanIndex', x))],
  plannerWindow.rootObject().importLabNotes: [labMap.importLabNotes],
  header.onMoved: [(lambda x, y: options.update({'mainWindowPosition': [x, y]}))]
})

app.exec()
options.saveToFile()
