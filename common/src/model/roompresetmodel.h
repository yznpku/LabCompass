#ifndef ROOMPRESETMODEL_H
#define ROOMPRESETMODEL_H

#include "stdafx.h"
#include "model/navigationdata.h"

class RoomPresetModel : public QObject
{
  Q_OBJECT

  QML_READONLY_VAR_PROPERTY(QVariantList, presets)
  QML_READONLY_VAR_PROPERTY(QString, current)

public:
  RoomPresetModel(QObject* parent = nullptr);
  void loadFromData(const NavigationData& data);
};

#endif // ROOMPRESETMODEL_H
