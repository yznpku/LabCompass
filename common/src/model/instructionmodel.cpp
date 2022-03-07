#include "stdafx.h"

#include "helper/roompresethelper.h"
#include "instructionmodel.h"

static const QStringList LOOT_LIST {
    "Switch puzzle",
    "Floor puzzle",
    "Escort gauntlet",
    "Trap gauntlet",
    "darkshrine",
    "argus",
    "golden-key",
    "silver-key",
    "silver-door",
};
static const QStringList MAJOR_LOOT_LIST {
    "golden-key",
    "silver-key",
    "silver-door",
};
static const QList<DirectionCode> REGULAR_DIRECTION_LIST { "N", "NE", "E", "SE", "S", "SW", "W", "NW" };

InstructionModel::InstructionModel(QObject* parent)
    : QObject(parent)
{
    m_roomHasPortal = false;
    m_atTrialRoom = false;
    m_hasNextRoom = false;
    m_nextRoomIsPreviousRoom = false;
    m_nextRoomIsUnmarkedOppositeDirection = false;
    m_finishedSections = 0;
    m_currentSection = -1;
    m_shouldKillIzaro = false;
}

void InstructionModel::loadFromData(const NavigationData& data)
{
    if (!data.currentRoomDetermined)
        return;

    updateRoomPreset(data);

    updateContentsAndLocations(data);

    updateExitLocations(data);

    update_currentSection(data.lab->getRoomFromId(data.currentRoom).section);

    update_roomHasPortal(false);

    update_atTrialRoom(data.lab->roomIsTrial(data.currentRoom));

    update_hasNextRoom(data.plannedRoute.size() >= 2);

    if (get_hasNextRoom()) {
        auto nextRoomId = data.plannedRoute[1];
        auto connections = data.lab->getRoomConnections(data.currentRoom)[nextRoomId];

        update_nextRoomIsPreviousRoom(nextRoomId == data.previousRoom);

        update_nextRoomIsUnmarkedOppositeDirection(!get_nextRoomIsPreviousRoom() && data.lab->roomIsTrial(data.currentRoom) && data.lab->getRoomFromId(data.currentRoom).section == data.lab->getRoomFromId(nextRoomId).section);

        update_nextRoomName(data.lab->getRoomFromId(nextRoomId).name);

        if (connections.isEmpty())
            update_nextRoomConnectionType("none"); // should not happen
        else if (connections.contains("P"))
            update_nextRoomConnectionType("portal");
        else if (connections.first() == "C")
            update_nextRoomConnectionType("secret");
        else
            update_nextRoomConnectionType("door");

        update_nextRoomDirection(connections.isEmpty() ? "" : connections.first());
    }

    if (data.lab->roomIsTrial(data.currentRoom)) {
        update_shouldKillIzaro(data.plannedRoute.size() < 2 || data.lab->getRoomFromId(data.currentRoom).section < data.lab->getRoomFromId(data.plannedRoute[1]).section);

        update_izaroMechanics(get_currentSection() < 2 ? data.lab->sectionMechanics[get_currentSection()] : "");
    }
}

void InstructionModel::updateRoomPreset(const NavigationData& data)
{
    const auto& room = data.lab->getRoomFromId(data.currentRoom);
    const auto& helper = RoomPresetHelper::instance;
    const auto& preset = helper->getPresetByAreaCode(room.areaCode);
    update_preset(preset);
}

void InstructionModel::updateExitLocations(const NavigationData& data)
{
    const auto& room = data.lab->getRoomFromId(data.currentRoom);
    const auto& helper = RoomPresetHelper::instance;
    const auto& preset = helper->getPresetByAreaCode(room.areaCode);

    QVariantList doorExitLocations;

    if (preset.isEmpty()) {
        const auto& exits = data.lab->getRoomConnections(data.currentRoom);
        for (const auto& l : exits.values())
            for (const auto& direction : l)
                if (REGULAR_DIRECTION_LIST.contains(direction))
                    doorExitLocations.append(QVariantMap { { "direction", direction }, { "tileRect", QRectF() } });

    } else {
        doorExitLocations = helper->getDoorExitLocationModel(preset);
    }

    update_doorExitLocations(doorExitLocations);
}

void InstructionModel::updateContentsAndLocations(const NavigationData& data)
{
    const auto& room = data.lab->getRoomFromId(data.currentRoom);
    const auto& contents = room.contents;
    QStringList loot;
    QStringList majorLoot;
    QStringList minorLoot;

    const auto& helper = RoomPresetHelper::instance;
    const auto& preset = helper->getPresetByAreaCode(room.areaCode);

    for (const auto& content : contents)
        if (LOOT_LIST.contains(content)) {
            loot.append(content);
            if (MAJOR_LOOT_LIST.contains(content))
                majorLoot.append(content);
            else
                minorLoot.append(content);
        }
    update_roomLoot(loot);

    if (data.lab->roomHasSecretPassage(data.currentRoom)) {
        loot.append("secret_passage");
        minorLoot.append("secret_passage");
    }

    QVariantList visibleContentLocations;
    if (!loot.isEmpty())
        visibleContentLocations = helper->getContentLocationModel(preset, true, !majorLoot.isEmpty(), !minorLoot.isEmpty());

    update_contentLocations(visibleContentLocations);
}
