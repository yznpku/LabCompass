#ifndef WIDGET_H
#define WIDGET_H

#include "stdafx.h"
#include "settings.h"

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
  Q_OBJECT

  Ui::Widget* ui;
  Settings* settings;

public:
  Widget(Settings* settings, QWidget* parent = 0);
  ~Widget();
  QString getClientPath() const;
  QString getClientId() const;

signals:
  void labStarted();
  void izaroBattleStarted();
  void sectionFinished();
  void labFinished();
  void roomChanged(const QString& room);

private:
  void loadMapFile(const QString& fileName);
};

#endif // WIDGET_H
