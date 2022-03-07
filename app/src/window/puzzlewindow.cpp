#include "puzzlewindow.h"

PuzzleWindow::PuzzleWindow(QQmlEngine* engine)
    : Window(engine, false)
{
    setSource(QUrl("qrc:/ui/Puzzle.qml"));

    connect(global(), SIGNAL(puzzleWindowOpenChanged()),
        this, SLOT(onWindowOpenChanged()));
}

void PuzzleWindow::onWindowOpenChanged()
{
    bool open = global()->property("puzzleWindowOpen").toBool();
    setVisible(open);
    rootObject()->setProperty("switchModel", 0);
    rootObject()->setProperty("guideModel", 0);
}
