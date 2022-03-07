#ifndef PUZZLEWINDOW_H
#define PUZZLEWINDOW_H

#include "stdafx.h"
#include "window/window.h"

class PuzzleWindow : public Window {
    Q_OBJECT

public:
    PuzzleWindow(QQmlEngine* engine);

private slots:
    void onWindowOpenChanged();
};

#endif // PUZZLEWINDOW_H
