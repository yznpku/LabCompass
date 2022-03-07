#ifndef VERSIONCHECKER_H
#define VERSIONCHECKER_H

#include "model/applicationmodel.h"
#include "stdafx.h"

class VersionChecker : public QObject {
    Q_OBJECT

    QNetworkAccessManager nam;

    ApplicationModel* model;
    QTimer timer;

public:
    VersionChecker(ApplicationModel* model, QObject* parent = nullptr);

private slots:
    void work();
    void onReplyFinished();
};

#endif // VERSIONCHECKER_H
