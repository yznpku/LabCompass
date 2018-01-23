#include "instructionlistwindow.h"

InstructionListWindow::InstructionListWindow(QQmlEngine* engine) : Window(engine, true)
{
  setSource(QUrl("qrc:/ui/instruction/InstructionList.qml"));
}
