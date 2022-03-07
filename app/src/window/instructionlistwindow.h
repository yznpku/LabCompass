#ifndef INSTRUCTIONLISTWINDOW_H
#define INSTRUCTIONLISTWINDOW_H

#include "window/window.h"

class InstructionListWindow : public Window {
    Q_OBJECT

public:
    InstructionListWindow(QQmlEngine* engine);

public slots:
    void onRoomChanged();
    void onIzaroBattleStarted();

private slots:
    void onCompassVisibleChanged();
};

#endif // INSTRUCTIONLISTWINDOW_H
