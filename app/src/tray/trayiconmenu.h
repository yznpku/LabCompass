#ifndef TRAYICONMENU_H
#define TRAYICONMENU_H

class TrayIconMenu : public QMenu {
    std::unique_ptr<QAction> resetAction;
    std::unique_ptr<QAction> quitAction;

public:
    TrayIconMenu();

private:
    void addResetAction();
    void addQuitAction();
};

#endif // TRAYICONMENU_H
