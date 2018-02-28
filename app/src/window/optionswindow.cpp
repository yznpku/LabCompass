#include "optionswindow.h"

OptionsWindow::OptionsWindow(QQmlEngine* engine, Settings* settings) : Window(engine, false, true)
{
  this->settings = settings;

  setSource(QUrl("qrc:/ui/Options.qml"));

  connect(global(), SIGNAL(optionsWindowOpenChanged()),
          this, SLOT(onWindowOpenChanged()));
  connect(rootObject(), SIGNAL(openUrl(QString)),
          this, SLOT(onOpenUrl(QString)));
  connect(rootObject(), SIGNAL(browseClientPath()),
          this, SLOT(onBrowseClientPath()));
  connect(rootObject(), SIGNAL(save()),
          this, SLOT(save()));
}

void OptionsWindow::onWindowOpenChanged()
{
  bool open = global()->property("optionsWindowOpen").toBool();

  if (open)
    load();

  setVisible(open);
}

void OptionsWindow::onBrowseClientPath()
{
  auto file = QFileDialog::getOpenFileName(this, "Find Game Client", "", "Path of Exile Client (*.exe)");
  if (!file.isEmpty())
     rootObject()->setProperty("clientPath", QFileInfo(file).dir().absolutePath());
}

void OptionsWindow::onOpenUrl(const QString& url)
{
  global()->setProperty("optionsWindowOpen", false);
  QDesktopServices::openUrl(QUrl(url));
}

void OptionsWindow::load()
{
  foreach (const QString& name, settingNames) {
    rootObject()->setProperty(name.toLocal8Bit().constData(), settings->value(name));
  }
}

void OptionsWindow::save()
{
  foreach (const QString& name, settingNames) {
    settings->setValue(name, rootObject()->property(name.toLocal8Bit().constData()));
  }
}
