#include "stdafx.h"

#include "application.h"

Application::Application(int& argc, char** argv)
    : QApplication(argc, argv)
{
    settings.reset(new Settings());
    settings->load();

    widget.reset(new Widget(settings.get()));
    widget->show();

    connect(widget.get(), &Widget::labStarted,
        this, &Application::onLabStarted);
    connect(widget.get(), &Widget::izaroBattleStarted,
        this, &Application::onIzaroBattleStarted);
    connect(widget.get(), &Widget::sectionFinished,
        this, &Application::onSectionFinished);
    connect(widget.get(), &Widget::labFinished,
        this, &Application::onLabFinished);
    connect(widget.get(), &Widget::roomChanged,
        this, &Application::onRoomChanged);
}

void Application::onLabStarted()
{
    addLogLine("Izaro: Ascend with precision.");
}

void Application::onIzaroBattleStarted()
{
    addLogLine("Izaro: Complex machinations converge to a single act of power.");
}

void Application::onSectionFinished()
{
    addLogLine("Izaro: By the Goddess! What ambition!");
}

void Application::onLabFinished()
{
    addLogLine("Izaro: I die for the Empire!");
}

void Application::onRoomChanged(const QString& roomName)
{
    addLogLine(QString(": You have entered %1.").arg(roomName));
}

void Application::addLogLine(const QString& s)
{
    const auto& clientId = widget->getClientId();
    const auto& line = QString("2018/01/01 00:00:00 0000000000 xxx [INFO Client %1] %2\n").arg(clientId, s);
    QFile file(QDir(widget->getClientPath()).absoluteFilePath("logs/Client.txt"));
    if (!file.open(QIODevice::WriteOnly | QIODevice::Append | QIODevice::Text))
        return;
    file.write(line.toUtf8());
}
