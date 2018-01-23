#include "applicationmodel.h"

ApplicationModel::ApplicationModel(QObject* parent) : QObject(parent)
{
  update_settings(new Settings("FutureCode", "LabCompass"));

  update_labyrinthModel(new LabyrinthModel);
  update_roomModel(new RoomModel);
  update_connectionModel(new ConnectionModel);
  update_plannedRouteModel(new PlannedRouteModel);
  update_goldenDoorModel(new GoldenDoorModel);
  update_instructionModel(new InstructionModel);
  update_planSummaryModel(new PlanSummaryModel);

  update_newVersionAvailable(false);
  update_labMapOutdated(true);
  update_logFileOpen(true);
  update_inLab(false);
  update_currentRoomDetermined(true);
  update_isValid(false);
}

bool ApplicationModel::loadFromFile(const QString& file)
{
  LabyrinthData newLabyrinthData;
  if (newLabyrinthData.loadFromFile(file)) {
    labyrinthData = newLabyrinthData;
    update_labMapOutdated(labyrinthData.date != QDateTime::currentDateTimeUtc().date());
    updatePlanData(PlanData());

    update_inLab(false);
    update_isValid(true);
    resetModels();
    return true;
  }
  return false;
}

void ApplicationModel::updatePlanData(const PlanData& planData)
{
  this->planData = planData;
  NavigationData navigationData;
  navigationData.loadFromData(&labyrinthData, planData);
  navigationData.updatePlannedRouteAndInstructions();

  get_planSummaryModel()->loadFromData(navigationData);
  updateNavigationData(navigationData);
}

void ApplicationModel::updateNavigationData(const NavigationData& navigationData)
{
  this->navigationData = navigationData;
  update_currentRoomDetermined(navigationData.currentRoomDetermined);
  updateModels();
}

void ApplicationModel::resetModels()
{
  get_labyrinthModel()->loadFromData(labyrinthData);
  get_roomModel()->loadFromData(labyrinthData, navigationData);
  get_connectionModel()->loadFromData(labyrinthData, navigationData);
  get_goldenDoorModel()->loadFromData(labyrinthData);
  get_plannedRouteModel()->loadFromData(navigationData);
  get_instructionModel()->loadFromData(navigationData);
}

void ApplicationModel::updateModels()
{
  get_roomModel()->updateFromData(navigationData);
  get_connectionModel()->updateFromData(navigationData);
  get_plannedRouteModel()->loadFromData(navigationData);
  get_instructionModel()->loadFromData(navigationData);
}
