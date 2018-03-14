#ifndef VERSIONCHECKER_H
#define VERSIONCHECKER_H

#include "stdafx.h"
#include "model/applicationmodel.h"

class VersionChecker : public QObject
{
  Q_OBJECT

  QThread networkThread;
  std::unique_ptr<QNetworkAccessManager> nam;

  ApplicationModel* model;
  QTimer timer;

public:
  VersionChecker(ApplicationModel* model, QObject* parent = nullptr);
  ~VersionChecker();

private slots:
  void work();
  void onReplyFinished();
};

#endif // VERSIONCHECKER_H
