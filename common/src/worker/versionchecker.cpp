#include "stdafx.h"

#include "global.h"
#include "versionchecker.h"

VersionChecker::VersionChecker(ApplicationModel* model, QObject* parent)
    : QObject(parent)
{
    this->model = model;

    nam.get(QNetworkRequest(QUrl("https://api.github.com/")));

    timer.setInterval(1000);
    timer.setSingleShot(false);
    timer.start();
    connect(&timer, &QTimer::timeout,
        this, &VersionChecker::work);
}

void VersionChecker::work()
{
    auto latestVersion = model->get_settings()->get_latestVersion();
    model->update_newVersionAvailable(!latestVersion.isEmpty() && latestVersion != VERSION);

    auto now = QDateTime::currentSecsSinceEpoch();
    if (now - model->get_settings()->get_lastVersionCheckAttempt() > 600 && now - model->get_settings()->get_lastVersionCheckSuccess() > 86400) {
        model->get_settings()->set_lastVersionCheckAttempt(now);

        qInfo() << "Checking github for latest version";
        auto reply = nam.get(QNetworkRequest(QUrl("https://api.github.com/repos/yznpku/LabCompass/releases/latest")));
        connect(reply, &QNetworkReply::finished,
            this, &VersionChecker::onReplyFinished);
    }
}

void VersionChecker::onReplyFinished()
{
    auto reply = reinterpret_cast<QNetworkReply*>(sender());

    if (reply->error() == QNetworkReply::NoError) {
        auto json = QJsonDocument::fromJson(reply->readAll());
        if (json.isObject() && json.object().contains("tag_name")) {
            auto latestVersion = json.object()["tag_name"].toString();
            model->get_settings()->set_latestVersion(latestVersion);
            model->get_settings()->set_lastVersionCheckSuccess(QDateTime::currentSecsSinceEpoch());

            qInfo() << "Received version checking response. Latest version:" << latestVersion;
        }
    }
    reply->deleteLater();
}
