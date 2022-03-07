#ifndef DATECHECKER_H
#define DATECHECKER_H

#include "model/applicationmodel.h"
#include "stdafx.h"

class DateChecker : public QObject {
    Q_OBJECT

    ApplicationModel* model;
    QTimer timer;

public:
    DateChecker(ApplicationModel* model, QObject* parent = nullptr);

private slots:
    void work();
};

#endif // DATECHECKER_H
