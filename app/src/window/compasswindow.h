#ifndef COMPASSWINDOW_H
#define COMPASSWINDOW_H

#include "stdafx.h"
#include "window/window.h"

class CompassWindow : public Window
{
public:
  CompassWindow(QQmlEngine* engine);
public slots:
  void restartTimer();
  void stopTimer();
  void closeTimer();
};

#endif // COMPASSWINDOW_H
