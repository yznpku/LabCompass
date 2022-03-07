#ifndef COMPASSWINDOW_H
#define COMPASSWINDOW_H

#include "stdafx.h"
#include "window/window.h"

class CompassWindow : public Window {
    Q_OBJECT

public:
    CompassWindow(QQmlEngine* engine);

public slots:
    void restartTimer();
    void stopTimer();
    void closeTimer();

private slots:
    void onCompassVisibleChanged();
};

#endif // COMPASSWINDOW_H
