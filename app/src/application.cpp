#include "application.h"
#include "version.h"

Application::Application(int argc, char** argv) : QApplication(argc, argv)
{
  initApplication();
  initResources();
  initSettings();
  initWindows();
  initWorkers();
  initControllers();
}

void Application::initApplication()
{
  setOrganizationName("FutureCode");
  setApplicationName("LabCompass");
}

void Application::initResources()
{
  QQuickStyle::setStyle("Material");

  qmlRegisterSingletonType(QUrl("qrc:/ui/Global.qml"), "com.labcompass", 1, 0, "Global");
  engine.load(QUrl("qrc:/ui/GlobalAccessor.qml"));

  auto global = engine.rootObjects()[0]->property("o").value<QObject*>();
  global->setProperty("model", QVariant::fromValue<QObject*>(&model));
  global->setProperty("version", VERSION);
#ifdef QT_DEBUG
  global->setProperty("debug", true);
#endif

  QFontDatabase::addApplicationFont(":/Fontin-SmallCaps.ttf");
  QFontDatabase::addApplicationFont(":/OpenSans-Regular.ttf");
  QFont font("Fontin SmallCaps");
  font.setPixelSize(16);
  setFont(font);
}

void Application::initSettings()
{
  QVariantMap defaultSettings {
    {"mainWindowPosition", QPoint(-1, -1)},
    {"poeClientPath", ""},
    {"latestVersion", ""},
    {"lastVersionCheckAttempt", 0LL},
    {"lastVersionCheckSuccess", 0LL},
    {"portalSkipsSection", true},
    {"multiclientSupport", false},
    {"scaleFactor", "1"},
  };
  for (auto i = defaultSettings.constBegin(); i != defaultSettings.constEnd(); i++)
    if (!model.get_settings()->contains(i.key()))
      model.get_settings()->setValue(i.key(), i.value());

  if (model.get_settings()->value("version").toString() != VERSION) {
    model.get_settings()->setValue("version", VERSION);
    model.get_settings()->setValue("latestVersion", "");
    model.get_settings()->setValue("lastVersionCheckAttempt", 0LL);
    model.get_settings()->setValue("lastVersionCheckSuccess", 0LL);
  }
}

void Application::initWindows()
{
  dummyWindow.reset(new Window(&engine, true));
  dummyWindow->setSource(QUrl("qrc:/ui/Dummy.qml"));
  dummyWindow->show();

  headerWindow.reset(new HeaderWindow(&engine));
  connect(headerWindow.get(), &HeaderWindow::moved,
          [this](int x, int y) { model.get_settings()->setValue("mainWindowPosition", QPoint(x, y)); });

  auto mainWindowPosition = model.get_settings()->value("mainWindowPosition").toPoint();
  auto screenGeometry = headerWindow->quickWindow()->screen()->geometry();
  if (!screenGeometry.contains(mainWindowPosition))
    mainWindowPosition = screenGeometry.center();
  headerWindow->move(mainWindowPosition);

  compassWindow.reset(new CompassWindow(&engine));
  compassWindow->setParentWindow(headerWindow.get(), QPoint(-48, 26));

  toolbarWindow.reset(new ToolbarWindow(&engine));
  toolbarWindow->setParentWindow(headerWindow.get(), QPoint(124, 28));

  instructionListWindow.reset(new InstructionListWindow(&engine));
  instructionListWindow->setParentWindow(headerWindow.get(), QPoint(-112, 186));

  headerWindow->show();
  compassWindow->show();
  toolbarWindow->show();
  instructionListWindow->show();

  plannerWindow.reset(new PlannerWindow(&engine));

  puzzleWindow.reset(new PuzzleWindow(&engine));
  puzzleWindow->setParentWindow(headerWindow.get(), QPoint(-122, 220));

  optionsWindow.reset(new OptionsWindow(&engine, model.get_settings()));
}

void Application::initWorkers()
{
  logWatcher.reset(new LogWatcher(&model));
  connect(logWatcher.get(), &LogWatcher::labStarted,
          compassWindow.get(), &CompassWindow::restartTimer);
  connect(logWatcher.get(), &LogWatcher::labFinished,
          compassWindow.get(), &CompassWindow::stopTimer);
  connect(logWatcher.get(), &LogWatcher::labExit,
          compassWindow.get(), &CompassWindow::closeTimer);

  versionChecker.reset(new VersionChecker(&model));
}

void Application::initControllers()
{
  labyrinthController.reset(new LabyrinthController(&model));
  connect(plannerWindow.get(), &PlannerWindow::importFile,
          labyrinthController.get(), &LabyrinthController::importFile);

  navigationController.reset(new NavigationController(&model));
  connect(logWatcher.get(), &LogWatcher::labStarted,
          navigationController.get(), &NavigationController::onLabStarted);
  connect(logWatcher.get(), &LogWatcher::sectionFinished,
          navigationController.get(), &NavigationController::onSectionFinished);
  connect(logWatcher.get(), &LogWatcher::labExit,
          navigationController.get(), &NavigationController::onLabExit);
  connect(logWatcher.get(), &LogWatcher::roomChanged,
          navigationController.get(), &NavigationController::onRoomChanged);
  connect(logWatcher.get(), &LogWatcher::portalSpawned,
          navigationController.get(), &NavigationController::onPortalSpawned);

  connect(plannerWindow.get(), &PlannerWindow::setRoomIsTarget,
          navigationController.get(), &NavigationController::onRoomIsTargetSet);
  connect(plannerWindow.get(), &PlannerWindow::setCurrentRoom,
          navigationController.get(), &NavigationController::onRoomIdSet);
}
