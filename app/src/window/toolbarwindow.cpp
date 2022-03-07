#include "toolbarwindow.h"

ToolbarWindow::ToolbarWindow(QQmlEngine* engine)
    : Window(engine, false)
{
    setSource(QUrl("qrc:/ui/Toolbar.qml"));

    connect(global(), SIGNAL(compassVisibleChanged()),
        this, SLOT(onCompassVisibleChanged()));
}

void ToolbarWindow::onCompassVisibleChanged()
{
    bool visible = global()->property("compassVisible").toBool();
    setVisible(visible);
}
