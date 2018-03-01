#include "headerwindow.h"

HeaderWindow::HeaderWindow(QQmlEngine* engine) : Window(engine, false)
{
  setSource(QUrl("qrc:/ui/Header.qml"));
  connect(rootObject(), SIGNAL(drag(int, int)),
          this, SLOT(onDrag(int, int)));
  connect(rootObject(), SIGNAL(exit()),
          QCoreApplication::instance(), SLOT(quit()));
}

void HeaderWindow::onDrag(int dx, int dy)
{
  move(x() + dx, y() + dy);
  emit moved(x(), y());
}
