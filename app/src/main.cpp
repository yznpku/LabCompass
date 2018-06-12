#include "application.h"

int main(int argc, char** argv)
{
  Q_INIT_RESOURCE(common);

  QSettings settings("FutureCode", "LabCompass");
  const auto& scaleFactor = settings.value("scaleFactor", "1").toByteArray();
  qputenv("QT_SCALE_FACTOR", scaleFactor);

  qputenv("QML_DISABLE_DISK_CACHE", "1");
  qputenv("QT_QUICK_CONTROLS_MATERIAL_THEME", "Dark");
  qputenv("QT_QUICK_CONTROLS_MATERIAL_ACCENT", "#2196F3");
  Application app(argc, argv);
  return app.exec();
}
