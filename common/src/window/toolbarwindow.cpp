#include "toolbarwindow.h"

ToolbarWindow::ToolbarWindow(QQmlEngine* engine) : Window(engine, false)
{
  setSource(QUrl("qrc:/ui/Toolbar.qml"));
}
