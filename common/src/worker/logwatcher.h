#ifndef LOGWATCHER_H
#define LOGWATCHER_H

#include "stdafx.h"
#include "model/applicationmodel.h"

class LogWatcher : public QObject
{
  Q_OBJECT

  ApplicationModel* model;
  QTimer timer;
  QString clientPath;
  std::unique_ptr<QFile> file;

signals:
  void labStarted();
  void labFinished();
  void sectionFinished();
  void labExit();
  void roomChanged(QString name);

public:
  LogWatcher(ApplicationModel* model);

private slots:
  void work();

private:
  void parseLine(const QString line);
  QString findGameClientPath();
};

#endif // LOGWATCHER_H
