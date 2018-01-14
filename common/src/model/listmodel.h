#ifndef LISTMODEL_H
#define LISTMODEL_H

#include "stdafx.h"

class ListModel : public QAbstractListModel
{
  Q_OBJECT

public:
  ListModel() {}
  ~ListModel() {}

public:
  Q_INVOKABLE int size() const;
  Q_INVOKABLE QVariantMap get(int row) const;
};

#endif // LISTMODEL_H
