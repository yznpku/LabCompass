#include "application.h"

int main(int argc, char** argv)
{
  QSettings settings("FutureCode", "LabCompass");
  auto scaleFactor = settings.value("scaleFactor", "1").toByteArray();
  qputenv("QT_SCALE_FACTOR", scaleFactor);

  qputenv("QML_DISABLE_DISK_CACHE", "1");
  Application app(argc, argv);
  return app.exec();
}
