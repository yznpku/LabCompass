#include "versionchecker.h"
#include "version.h"

VersionChecker::VersionChecker(ApplicationModel* model, QObject* parent) : QObject(parent)
{
  this->model = model;

  moveToThread(&networkThread);
  networkThread.start();

  timer.setInterval(1000);
  timer.setSingleShot(false);
  timer.start();
  connect(&timer, &QTimer::timeout,
          this, &VersionChecker::work);
}

VersionChecker::~VersionChecker()
{
  networkThread.terminate();
  networkThread.wait();
}

void VersionChecker::work()
{
  auto latestVersion = model->get_settings()->value("latestVersion").toString();
  model->update_newVersionAvailable(!latestVersion.isEmpty() && latestVersion != VERSION);

  auto now = QDateTime::currentSecsSinceEpoch();
  if (now - model->get_settings()->value("lastVersionCheckAttempt").toLongLong() > 600 &&
      now - model->get_settings()->value("lastVersionCheckSuccess").toLongLong() > 86400) {
    model->get_settings()->setValue("lastVersionCheckAttempt", now);

    if (!nam.get())
      nam.reset(new QNetworkAccessManager());
    auto reply = nam->get(QNetworkRequest(QUrl("https://api.github.com/repos/yznpku/LabCompass/releases/latest")));

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
      model->get_settings()->setValue("latestVersion", latestVersion);
      model->get_settings()->setValue("lastVersionCheckSuccess", QDateTime::currentSecsSinceEpoch());
    }
  }
  reply->deleteLater();
}
