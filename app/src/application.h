#ifndef APPLICATION_H
#define APPLICATION_H

#include "stdafx.h"
#include "model/applicationmodel.h"
#include "window/headerwindow.h"
#include "window/compasswindow.h"
#include "window/compasstoolbarwindow.h"
#include "window/toolbarwindow.h"
#include "window/instructionlistwindow.h"
#include "window/plannerwindow.h"
#include "window/puzzlewindow.h"
#include "window/optionswindow.h"
#include "worker/logwatcher.h"
#include "worker/versionchecker.h"
#include "worker/datechecker.h"
#include "controller/labyrinthcontroller.h"
#include "controller/navigationcontroller.h"
#include "hotkey/hotkeybinding.h"

class Application : public QApplication
{
  Q_OBJECT

  ApplicationModel model;
  QQmlApplicationEngine engine;
  QObject* global;

  std::unique_ptr<QSystemTrayIcon> trayIcon;
  std::unique_ptr<QMenu> trayIconMenu;

  std::unique_ptr<Window> dummyWindow;
  std::unique_ptr<HeaderWindow> headerWindow;
  std::unique_ptr<CompassWindow> compassWindow;
  std::unique_ptr<CompassToolbarWindow> compassToolbarWindow;
  std::unique_ptr<ToolbarWindow> toolbarWindow;
  std::unique_ptr<InstructionListWindow> instructionListWindow;
  std::unique_ptr<PlannerWindow> plannerWindow;
  std::unique_ptr<PuzzleWindow> puzzleWindow;
  std::unique_ptr<OptionsWindow> optionsWindow;

  std::unique_ptr<LogWatcher> logWatcher;
  std::unique_ptr<VersionChecker> versionChecker;
  std::unique_ptr<DateChecker> dateChecker;

  std::unique_ptr<LabyrinthController> labyrinthController;
  std::unique_ptr<NavigationController> navigationController;

  std::unique_ptr<HotkeyBinding> toggleHideUiHotkey;

public:
  Application(int& argc, char** argv);

private slots:
  void onAboutToQuit();

private:
  void init();
  void initResources();
  void initSystemTrayIcon();
  void initHelpers();
  void initWindows();
  void initWorkers();
  void initControllers();
  void initHotkeys();

  void restorePreviouslyLoadedMap();
};

#endif // APPLICATION_H
