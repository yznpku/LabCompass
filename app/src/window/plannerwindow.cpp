#include "plannerwindow.h"

PlannerWindow::PlannerWindow(QQmlEngine* engine) : Window(engine, false)
{
  setSource(QUrl("qrc:/ui/planner/Planner.qml"));

  connect(rootObject(), SIGNAL(drag(int, int)),
          this, SLOT(onDrag(int, int)));
  connect(global(), SIGNAL(plannerWindowOpenChanged()),
          this, SLOT(onWindowOpenChanged()));
  connect(rootObject(), SIGNAL(importLabNotesButtonClicked()),
          this, SLOT(onImportLabNotesFileClicked()));
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
  auto downloadLocations = QStandardPaths::standardLocations(QStandardPaths::DownloadLocation);
  auto fileName = QFileDialog::getOpenFileName(nullptr, "Import Lab Notes",
                                               downloadLocations.isEmpty() ? "" : downloadLocations[0],
                                               "Lab Notes (*.json)");
  if (!fileName.isEmpty())
    emit importFile(fileName);
}

void PlannerWindow::onOpenUrl(const QString& url)
{
  global()->setProperty("plannerWindowOpen", false);
  QDesktopServices::openUrl(QUrl(url));
}

void PlannerWindow::onDrag(int dx, int dy)
{
  move(x() + dx, y() + dy);
  emit moved(x(), y());
}
