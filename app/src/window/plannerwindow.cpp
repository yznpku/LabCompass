#include "plannerwindow.h"
#include "settings.h"

PlannerWindow::PlannerWindow(QQmlEngine* engine) : Window(engine, false)
{
  setSource(QUrl("qrc:/ui/planner/Planner.qml"));

  connect(rootObject(), SIGNAL(drag(int, int)),
          this, SLOT(onDrag(int, int)));
  connect(global(), SIGNAL(plannerWindowOpenChanged()),
          this, SLOT(onWindowOpenChanged()));
  connect(rootObject(), SIGNAL(importLabNotesButtonClicked()),
          this, SLOT(onImportLabNotesFileClicked()));
  connect(rootObject(), SIGNAL(importLabNotesFromUrl(QUrl)),
          this, SLOT(onImportLabNotesFromUrl(QUrl)));
  connect(rootObject(), SIGNAL(openUrl(QString)),
          this, SLOT(onOpenUrl(QString)));

  connect(rootObject()->findChild<QObject*>("labyrinthMapDisplay"), SIGNAL(setRoomIsTarget(QString, bool)),
          this, SIGNAL(setRoomIsTarget(QString, bool)));
  connect(rootObject()->findChild<QObject*>("labyrinthMapDisplay"), SIGNAL(setCurrentRoom(QString)),
          this, SIGNAL(setCurrentRoom(QString)));
}

void PlannerWindow::onWindowOpenChanged()
{
  bool open = global()->property("plannerWindowOpen").toBool();
  setVisible(open);
}

void PlannerWindow::onImportLabNotesFileClicked()
{
  Settings* settings = global()->property("model").value<QObject*>()->property("settings").value<Settings*>();
  auto importDirectory = settings->get_importDirectory();
  if (importDirectory.isEmpty()) {
    auto downloadLocations = QStandardPaths::standardLocations(QStandardPaths::DownloadLocation);
    if (!downloadLocations.isEmpty())
      importDirectory = downloadLocations[0];
  }

  const auto& fileName = QFileDialog::getOpenFileName(nullptr, "Import Lab Notes",
                                                      importDirectory,
                                                      "Lab Maps (*.json *.map)");
  if (!fileName.isEmpty()) {
    importLabNotesFromFile(fileName);
  }
}

void PlannerWindow::onImportLabNotesFromUrl(const QUrl& url)
{
  if (url.isLocalFile())
    importLabNotesFromFile(url.toLocalFile());
}

void PlannerWindow::onOpenUrl(const QString& url)
{
  global()->setProperty("plannerWindowOpen", false);
  QDesktopServices::openUrl(QUrl(url));
}

void PlannerWindow::onDrag(int dx, int dy)
{
  move(x() + dx, y() + dy);
}

void PlannerWindow::importLabNotesFromFile(const QString& file)
{
  Settings* settings = global()->property("model").value<QObject*>()->property("settings").value<Settings*>();
  const auto& directory = QFileInfo(file).absoluteDir().absolutePath();
  settings->set_importDirectory(directory);
  emit importFile(file);
}
