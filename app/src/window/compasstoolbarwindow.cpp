#include "compasstoolbarwindow.h"

CompassToolbarWindow::CompassToolbarWindow(QQmlEngine* engine)
    : Window(engine, false)
{
    setSource(QUrl("qrc:/ui/compass/CompassToolbar.qml"));

    connect(global(), SIGNAL(compassToolbarVisibleChanged()),
        this, SLOT(onCompassToolbarVisibleChanged()));
}

void CompassToolbarWindow::onCompassToolbarVisibleChanged()
{
    bool open = global()->property("compassToolbarVisible").toBool();
    setVisible(open);
}
