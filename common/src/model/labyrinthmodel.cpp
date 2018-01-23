#include "labyrinthmodel.h"
#include "labyrinthdata.h"

LabyrinthModel::LabyrinthModel(QObject* parent) : QObject(parent)
{
}

void LabyrinthModel::loadFromData(const LabyrinthData& data)
{
  update_title(data.date.toString("yyyy-MM-dd") + ' ' + data.difficulty);
}
