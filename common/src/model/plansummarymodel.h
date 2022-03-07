#ifndef PLANSUMMARYMODEL_H
#define PLANSUMMARYMODEL_H

#include "model/navigationdata.h"

class PlanSummaryModel : public QObject {
    Q_OBJECT

    QML_READONLY_VAR_PROPERTY(int, rooms)
    QML_READONLY_VAR_PROPERTY(int, length)
    QML_READONLY_VAR_PROPERTY(int, argus)
    QML_READONLY_VAR_PROPERTY(int, troves)
    QML_READONLY_VAR_PROPERTY(int, darkshrines)
    QML_READONLY_VAR_PROPERTY(int, silverCaches)

public:
    PlanSummaryModel(QObject* parent = nullptr);
    void loadFromData(const NavigationData& data);
};

#endif // PLANSUMMARYMODEL_H
