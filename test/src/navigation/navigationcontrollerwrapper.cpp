#include "navigationcontrollerwrapper.h"

NavigationControllerWrapper::NavigationControllerWrapper(ApplicationModel* model)
{
  controller.reset(new NavigationController(model));
}

NavigationControllerWrapper* NavigationControllerWrapper::labStarted()
{
  controller->onLabStarted();
  return this;
}

NavigationControllerWrapper* NavigationControllerWrapper::sectionFinished()
{
  controller->onSectionFinished();
  return this;
}

NavigationControllerWrapper* NavigationControllerWrapper::labExit()
{
  controller->onLabExit();
  return this;
}

NavigationControllerWrapper* NavigationControllerWrapper::roomChanged(const QString& name)
{
  controller->onRoomChanged(name);
  return this;
}
