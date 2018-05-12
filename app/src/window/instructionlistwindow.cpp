#include "instructionlistwindow.h"

InstructionListWindow::InstructionListWindow(QQmlEngine* engine) : Window(engine, true)
{
  setSource(QUrl("qrc:/ui/instruction/InstructionList.qml"));

  connect(global(), SIGNAL(compassVisibleChanged()),
          this, SLOT(onCompassVisibleChanged()));
}

void InstructionListWindow::onCompassVisibleChanged()
{
  bool visible = global()->property("compassVisible").toBool();
  setVisible(visible);
}
