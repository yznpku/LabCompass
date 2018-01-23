#ifndef WINDOW_H
#define WINDOW_H

#include "stdafx.h"

class Window : public QQuickWidget
{
  Q_OBJECT
  Window* parentWindow {nullptr};
  QPoint parentOffset;
protected:
  bool takeFocus;

public:
  Window(QQmlEngine* engine, bool transparent = false, bool takeFocus = false, QWidget* parent = nullptr);
  void setParentWindow(Window* parent, const QPoint& offset);

protected:
  QObject* global();
  virtual void showEvent(QShowEvent* e);

private slots:
  void repositionToParent();
};

#endif // WINDOW_H
