#ifndef INSTRUCTIONLISTWINDOW_H
#define INSTRUCTIONLISTWINDOW_H

#include "stdafx.h"
#include "window/window.h"

class InstructionListWindow : public Window
{
  Q_OBJECT

public:
  InstructionListWindow(QQmlEngine* engine);

private slots:
  void onCompassVisibleChanged();
};

#endif // INSTRUCTIONLISTWINDOW_H
