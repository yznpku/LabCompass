#ifndef OPTIONSWINDOW_H
#define OPTIONSWINDOW_H

#include "stdafx.h"
#include "window/window.h"
#include "settings.h"

class OptionsWindow : public Window
{
  Q_OBJECT

  Settings* settings;

  QObject* clientPathInput {nullptr};

public:
  OptionsWindow(QQmlEngine* engine, Settings* settings);

private slots:
  void onWindowOpenChanged();
  void onBrowseClientPath();
  void onOpenUrl(const QString& url);
  void load();
  void save();
};

#endif // OPTIONSWINDOW_H
