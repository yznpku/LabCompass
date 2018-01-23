#include "application.h"

int main(int argc, char** argv)
{
//  qputenv("QT_SCALE_FACTOR", "2");
  qputenv("QML_DISABLE_DISK_CACHE", "1");
  Application app(argc, argv);
  return app.exec();
}
