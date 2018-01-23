#ifndef LABYRINTHMODEL_H
#define LABYRINTHMODEL_H

#include "stdafx.h"
#include "model/labyrinthdata.h"

class LabyrinthModel : public QObject
{
  Q_OBJECT

  QML_READONLY_VAR_PROPERTY(QString, title)

  QML_READONLY_VAR_PROPERTY(QString, difficulty)
  QML_READONLY_VAR_PROPERTY(QDate, date)

public:
  LabyrinthModel(QObject* parent = nullptr);
  void loadFromData(const LabyrinthData& data);
};

#endif // LABYRINTHMODEL_H
