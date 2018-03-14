#ifndef APPLICATION_H
#define APPLICATION_H

#include "stdafx.h"
#include "model/applicationmodel.h"
#include "window/headerwindow.h"
#include "window/compasswindow.h"
#include "window/toolbarwindow.h"
#include "window/instructionlistwindow.h"
#include "window/plannerwindow.h"
#include "window/puzzlewindow.h"
#include "window/optionswindow.h"
#include "worker/logwatcher.h"
#include "worker/versionchecker.h"
#include "controller/labyrinthcontroller.h"
#include "controller/navigationcontroller.h"

class Application : public QApplication
{
  Q_OBJECT

  ApplicationModel model;
  QQmlApplicationEngine engine;

  std::unique_ptr<QSystemTrayIcon> trayIcon;
  std::unique_ptr<QMenu> trayIconMenu;

  std::unique_ptr<Window> dummyWindow;
  std::unique_ptr<HeaderWindow> headerWindow;
  std::unique_ptr<CompassWindow> compassWindow;
  std::unique_ptr<ToolbarWindow> toolbarWindow;
  std::unique_ptr<InstructionListWindow> instructionListWindow;
  std::unique_ptr<PlannerWindow> plannerWindow;
  std::unique_ptr<PuzzleWindow> puzzleWindow;
  std::unique_ptr<OptionsWindow> optionsWindow;

  std::unique_ptr<LogWatcher> logWatcher;
  std::unique_ptr<VersionChecker> versionChecker;

  std::unique_ptr<LabyrinthController> labyrinthController;
  std::unique_ptr<NavigationController> navigationController;

public:
  Application(int argc, char** argv);

private:
  void initApplication();
  void initResources();
  void initSettings();
  void initSystemTrayIcon();
  void initWindows();
  void initWorkers();
  void initControllers();
};

#endif // APPLICATION_H
