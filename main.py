import sys

from PyQt5.QtCore import Qt, QUrl, QTimer
from PyQt5.QtWidgets import QApplication
from PyQt5.QtGui import QFont
from PyQt5.QtQml import qmlRegisterSingletonType, QQmlApplicationEngine
from PyQt5.QtQuick import QQuickView
from PyQt5.QtQuickWidgets import QQuickWidget

from window import TransparentWindow, CompassWindow, EditWindow, HeaderWindow, PlannerWindow, ToolbarWindow
from logwatcher import LogWatcher
from labmap import LabMap

app = QApplication(sys.argv)
font = QFont('consolas')
font.setPointSize(10)
QApplication.setFont(font)

engine = QQmlApplicationEngine()
dummy = TransparentWindow(engine, 'qml/Dummy.qml')
dummy.show()

qmlRegisterSingletonType(QUrl.fromLocalFile('qml/Global.qml'), 'com.labcompass', 1, 0, 'Global')
engine.load(QUrl.fromLocalFile('qml/GlobalAccessor.qml'))
Global = engine.rootObjects()[0].property('o')

labMap = LabMap()
Global.editWindowOpenChanged.connect(lambda: labMap.setEditMode(Global.property('editWindowOpen')))

logWatcher = LogWatcher()
QTimer.singleShot(0, logWatcher.start)

logWatcher.labStart.connect(labMap.labStart)
logWatcher.sectionComplete.connect(labMap.sectionComplete)
logWatcher.zoneChange.connect(labMap.enterZone)
logWatcher.labExit.connect(labMap.labExit)

header = HeaderWindow(engine)
header.show()

compass = CompassWindow(engine, parent=header, offset=(-10, 32))
compass.show()
labMap.roomChanged.connect(compass.updateRoom)
labMap.markPlan.connect(compass.markPlan)
logWatcher.labStart.connect(compass.restartTimer)
logWatcher.labFinish.connect(compass.stopTimer)
logWatcher.labExit.connect(compass.closeTimer)

toolbar = ToolbarWindow(engine, parent=header, offset=(0, 168))
toolbar.show()

editWindow = EditWindow(engine, labMap, parent=header, offset=(0, 220))
Global.editWindowOpenChanged.connect(lambda: editWindow.setVisible(Global.property('editWindowOpen')))

plannerWindow = PlannerWindow(engine, labMap, parent=header, offset=(-1020, 0))
Global.plannerWindowOpenChanged.connect(lambda: plannerWindow.setVisible(Global.property('plannerWindowOpen')))

app.exec()
