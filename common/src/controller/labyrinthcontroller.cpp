#include "labyrinthcontroller.h"

LabyrinthController::LabyrinthController(ApplicationModel* model)
{
  this->model = model;
}

void LabyrinthController::importFile(const QString& file)
{
  model->loadFromFile(file);
}
