#include "stdafx.h"

#include "roompresetswindow.h"

RoomPresetsWindow::RoomPresetsWindow(QQmlEngine* engine)
    : Window(engine, false)
{
    setSource(QUrl("qrc:/ui/roompresets/RoomPresets.qml"));

    roomPresetModel = global()->property("model").value<QObject*>()->property("roomPresetModel").value<QObject*>();

    connect(rootObject(), SIGNAL(drag(int, int)),
        this, SLOT(onDrag(int, int)));
    connect(rootObject(), SIGNAL(applyPresetButtonClicked(QString)),
        this, SLOT(onApplyPresetButtonClicked(QString)));
    connect(global(), SIGNAL(roomPresetsWindowOpenChanged()),
        this, SLOT(onWindowOpenChanged()));
    connect(roomPresetModel, SIGNAL(presetsChanged(QVariantList)),
        this, SLOT(resetIndex()));
}

void RoomPresetsWindow::onWindowOpenChanged()
{
    bool open = global()->property("roomPresetsWindowOpen").toBool();
    setVisible(open);
    resetIndex();
}

void RoomPresetsWindow::onDrag(int dx, int dy)
{
    move(x() + dx, y() + dy);
}

void RoomPresetsWindow::onApplyPresetButtonClicked(const QString& areaCode)
{
    const auto& roomId = roomPresetModel->property("roomId").toString();
    emit setRoomPreset(roomId, areaCode);
}

void RoomPresetsWindow::resetIndex()
{
    rootObject()->setProperty("presetListViewCurrentIndex", roomPresetModel->property("current").toInt());
}
