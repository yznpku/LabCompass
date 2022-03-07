#ifndef PLANNERWINDOW_H
#define PLANNERWINDOW_H

#include "window/window.h"

class PlannerWindow : public Window {
    Q_OBJECT

signals:
    void importFile(QString fileName);
    void setRoomIsTarget(QString id, bool target);
    void setCurrentRoom(QString id);

public:
    PlannerWindow(QQmlEngine* engine);

private slots:
    void onWindowOpenChanged();
    void onImportLabNotesFileClicked();
    void onImportLabNotesFromUrl(const QUrl& url);
    void onOpenUrl(const QString& url);
    void onDrag(int dx, int dy);

private:
    void importLabNotesFromFile(const QString& file);
};

#endif // PLANNERWINDOW_H
