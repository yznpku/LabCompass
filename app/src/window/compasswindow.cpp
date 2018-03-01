#include "compasswindow.h"

CompassWindow::CompassWindow(QQmlEngine* engine) : Window(engine, true)
{
  setSource(QUrl("qrc:/ui/Compass.qml"));
}

void CompassWindow::restartTimer()
{
  QMetaObject::invokeMethod(rootObject(), "restartTimer");
}

void CompassWindow::stopTimer()
{
  QMetaObject::invokeMethod(rootObject(), "stopTimer");
}

void CompassWindow::closeTimer()
{
  QMetaObject::invokeMethod(rootObject(), "closeTimer");
}
