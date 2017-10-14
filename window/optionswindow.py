from PyQt5.QtCore import QUrl
from PyQt5.QtGui import QDesktopServices
from window.template import OpaqueWindow


class OptionsWindow(OpaqueWindow):
  def __init__(self, engine, **kwargs):
    super().__init__(engine, 'qml/Options.qml', **kwargs)
    self.Global.optionsWindowOpenChanged.connect(self.onWindowOpenChanged)
    self.rootObject().openUrl.connect(self.openUrl)

  def onWindowOpenChanged(self):
    isOpen = self.Global.property('optionsWindowOpen')
    self.setVisible(isOpen)

  def openUrl(self, url):
    self.Global.setProperty('optionsWindowOpen', False)
    QDesktopServices.openUrl(QUrl(url))
