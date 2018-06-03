#include "datechecker.h"

DateChecker::DateChecker(ApplicationModel* model, QObject* parent) : QObject(parent)
{
  this->model = model;

  timer.setInterval(1000);
  timer.setSingleShot(false);
  timer.start();
  connect(&timer, &QTimer::timeout,
          this, &DateChecker::work);

  work();
}

void DateChecker::work()
{
  model->update_currentUtcDate(QDateTime::currentDateTimeUtc().date());
}
