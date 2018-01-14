#ifndef NAVIGATIONCONTROLLER_H
#define NAVIGATIONCONTROLLER_H

#include "stdafx.h"
#include "model/applicationmodel.h"

class NavigationController : public QObject
{
  Q_OBJECT

  ApplicationModel* model;

public:
  NavigationController(ApplicationModel* model);

public slots:
  void onLabStarted();
  void onSectionFinished();
  void onLabExit();
  void onRoomChanged(const QString& name);
  void onRoomIsTargetSet(const QString& id, bool isTarget);
  void onRoomIdSet(const QString& id);
};

#endif // NAVIGATIONCONTROLLER_H
