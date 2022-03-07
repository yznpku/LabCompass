#include "stdafx.h"

#include "labyrinthdata.h"
#include "labyrinthmodel.h"

LabyrinthModel::LabyrinthModel(QObject* parent)
    : QObject(parent)
{
}

void LabyrinthModel::loadFromData(const LabyrinthData& data)
{
    update_title(data.date.toString("yyyy-MM-dd") + ' ' + data.difficulty);
    update_difficulty(data.difficulty);
    update_date(data.date);
}
