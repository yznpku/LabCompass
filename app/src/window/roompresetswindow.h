#ifndef ROOMPRESETSWINDOW_H
#define ROOMPRESETSWINDOW_H

#include "stdafx.h"
#include "window/window.h"

class RoomPresetsWindow : public Window
{
  Q_OBJECT

  QObject* roomPresetModel;

public:
  RoomPresetsWindow(QQmlEngine* engine);

private slots:
  void onWindowOpenChanged();
  void onDrag(int dx, int dy);
  void resetIndex();
};

#endif // ROOMPRESETSWINDOW_H
