#include "optionswindow.h"

OptionsWindow::OptionsWindow(QQmlEngine* engine, Settings* settings) : Window(engine, false, true)
{
  this->settings = settings;

  setSource(QUrl("qrc:/ui/Options.qml"));

  clientPathInput = rootObject()->findChild<QObject*>("clientPathInput");

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
  auto file = QFileDialog::getOpenFileName(this, "Find Game Client", "", "Path of Exile Client (Client.exe;PathOfExileSteam.exe)");
  if (!file.isEmpty())
     clientPathInput->setProperty("text", QFileInfo(file).dir().absolutePath());
}

void OptionsWindow::onOpenUrl(const QString& url)
{
  global()->setProperty("optionsWindowOpen", false);
  QDesktopServices::openUrl(QUrl(url));
}

void OptionsWindow::load()
{
  clientPathInput->setProperty("text", settings->value("poeClientPath").toString());
}

void OptionsWindow::save()
{
  settings->setValue("poeClientPath", clientPathInput->property("text"));
}
