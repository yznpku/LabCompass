#ifndef OPTIONSWINDOW_H
#define OPTIONSWINDOW_H

#include "settings.h"
#include "window/window.h"

class OptionsWindow : public Window {
    Q_OBJECT

    Settings* settings;
    QStringList settingNames {
        "poeClientPath",
        "portalSkipsSection",
        "multiclientSupport",
        "showMinimap",
        "toggleHideUiHotkey",
    };

public:
    OptionsWindow(QQmlEngine* engine, Settings* settings);

private slots:
    void onWindowOpenChanged();
    void onBrowseClientPath();
    void onOpenUrl(const QString& url);
    void load();
    void save();
};

#endif // OPTIONSWINDOW_H
