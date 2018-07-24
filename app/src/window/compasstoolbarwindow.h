#ifndef COMPASSTOOLBARWINDOW_H
#define COMPASSTOOLBARWINDOW_H

#include "stdafx.h"
#include "window/window.h"

class CompassToolbarWindow : public Window
{
  Q_OBJECT

public:
  CompassToolbarWindow(QQmlEngine* engine);

private slots:
  void onCompassToolbarVisibleChanged();
};

#endif // COMPASSTOOLBARWINDOW_H
