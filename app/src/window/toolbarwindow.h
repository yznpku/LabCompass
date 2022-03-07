#ifndef TOOLBARWINDOW_H
#define TOOLBARWINDOW_H

#include "stdafx.h"
#include "window/window.h"

class ToolbarWindow : public Window {
    Q_OBJECT

public:
    ToolbarWindow(QQmlEngine* engine);

private slots:
    void onCompassVisibleChanged();
};

#endif // TOOLBARWINDOW_H
