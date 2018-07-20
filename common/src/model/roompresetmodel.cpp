#include "roompresetmodel.h"
#include "helper/roompresethelper.h"

RoomPresetModel::RoomPresetModel(QObject* parent) : QObject(parent)
{

}

void RoomPresetModel::loadFromData(const NavigationData& data)
{
  if (!data.currentRoomDetermined) {
    update_current("");
    update_presets({});

  } else {
    auto helper = RoomPresetHelper::instance;

    const auto& room = data.lab->getRoomFromId(data.currentRoom);
    const auto& presetList = helper->getPresetListByName(room.name, room.contents.contains("golden-door"));
    QVariantList presets;

    for (const auto& preset: presetList)
      presets.append(preset.second);

    update_current(room.areaCode);
    update_presets(presets);
  }
}
