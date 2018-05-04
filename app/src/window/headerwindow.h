#ifndef HEADERWINDOW_H
#define HEADERWINDOW_H

#include "stdafx.h"
#include "window/window.h"

class HeaderWindow : public Window
{
  Q_OBJECT

signals:
  void moved(int x, int y);

public:
  HeaderWindow(QQmlEngine* engine);

private slots:
  void onCompassVisibleChanged();
  void onDrag(int dx, int dy);
};

#endif // HEADERWINDOW_H
