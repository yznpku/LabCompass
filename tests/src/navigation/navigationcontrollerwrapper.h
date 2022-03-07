#ifndef NAVIGATIONCONTROLLERWRAPPER_H
#define NAVIGATIONCONTROLLERWRAPPER_H

#include "controller/navigationcontroller.h"

class NavigationControllerWrapper {

    std::unique_ptr<NavigationController> controller;

public:
    NavigationControllerWrapper(ApplicationModel* model);

public:
    NavigationControllerWrapper* labStarted();
    NavigationControllerWrapper* sectionFinished();
    NavigationControllerWrapper* labExit();
    NavigationControllerWrapper* roomChanged(const QString& name);
};

#endif // NAVIGATIONCONTROLLERWRAPPER_H
