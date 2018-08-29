#include "instructionlistwindow.h"

InstructionListWindow::InstructionListWindow(QQmlEngine* engine) : Window(engine, true)
{
  setSource(QUrl("qrc:/ui/instruction/InstructionList.qml"));

  connect(global(), SIGNAL(compassVisibleChanged()),
          this, SLOT(onCompassVisibleChanged()));
}

void InstructionListWindow::onRoomChanged()
{
  const auto& icon = rootObject()->findChild<QObject*>("izaroInstructionItemIcon");
  if (icon)
    icon->setProperty("state", "");
}

void InstructionListWindow::onIzaroBattleStarted()
{
  const auto& icon = rootObject()->findChild<QObject*>("izaroInstructionItemIcon");
  if (icon)
    QMetaObject::invokeMethod(icon, "onIzaroBattleStarted");
}

void InstructionListWindow::onCompassVisibleChanged()
{
  bool visible = global()->property("compassVisible").toBool();
  setVisible(visible);
}
