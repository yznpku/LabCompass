#ifndef LABYRINTHCONTROLLER_H
#define LABYRINTHCONTROLLER_H

#include "stdafx.h"
#include "model/applicationmodel.h"

class LabyrinthController : public QObject
{
  Q_OBJECT

  ApplicationModel* model;

public:
  LabyrinthController(ApplicationModel* model);

public slots:
  void importFile(const QString& file);
};

#endif // LABYRINTHCONTROLLER_H
