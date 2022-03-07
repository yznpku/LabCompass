#include "headerwindow.h"

HeaderWindow::HeaderWindow(QQmlEngine* engine)
    : Window(engine, false)
{
    setSource(QUrl("qrc:/ui/Header.qml"));

    connect(global(), SIGNAL(compassVisibleChanged()),
        this, SLOT(onCompassVisibleChanged()));
    connect(rootObject(), SIGNAL(drag(int, int)),
        this, SLOT(onDrag(int, int)));
    connect(rootObject(), SIGNAL(exit()),
        QCoreApplication::instance(), SLOT(quit()));
}

void HeaderWindow::onCompassVisibleChanged()
{
    bool visible = global()->property("compassVisible").toBool();
    setVisible(visible);
}

void HeaderWindow::onDrag(int dx, int dy)
{
    move(x() + dx, y() + dy);
    emit moved(x(), y());
}
