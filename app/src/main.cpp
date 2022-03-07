#include "stdafx.h"

#include "application.h"
#include "global.h"
#include "util/setupdebugoutput.h"

int main(int argc, char** argv)
{
    Q_INIT_RESOURCE(common);
    QApplication::setOrganizationName("FutureCode");
    QApplication::setApplicationName("LabCompass");

    setupDebugOutput();
    qInfo() << "Operating System:" << QSysInfo::prettyProductName();
    qInfo() << "LabCompass:" << VERSION;

    QSettings settings("FutureCode", "LabCompass");
    const auto& scaleFactor = settings.value("scaleFactor", "1").toByteArray();
    qputenv("QT_SCALE_FACTOR", scaleFactor);
    qInfo() << "Using scale factor:" << scaleFactor;

    qputenv("QML_DISABLE_DISK_CACHE", "1");
    qputenv("QT_QUICK_CONTROLS_MATERIAL_THEME", "Dark");
    qputenv("QT_QUICK_CONTROLS_MATERIAL_ACCENT", "#2196F3");

    Application app(argc, argv);
    int r = app.exec();
    qInfo() << "Exiting with code:" << r;
    return r;
}
