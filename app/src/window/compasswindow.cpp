#include "compasswindow.h"

CompassWindow::CompassWindow(QQmlEngine* engine) : Window(engine, true)
{
  setSource(QUrl("qrc:/ui/compass/Compass.qml"));

  connect(global(), SIGNAL(compassVisibleChanged()),
          this, SLOT(onCompassVisibleChanged()));
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

void CompassWindow::onCompassVisibleChanged()
{
  bool visible = global()->property("compassVisible").toBool();
  setVisible(visible);
}
