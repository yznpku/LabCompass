#include "roompresetmodel.h"
#include "helper/roompresethelper.h"

RoomPresetModel::RoomPresetModel(QObject* parent) : QObject(parent)
{
  m_current = -1;
}

void RoomPresetModel::loadFromData(const NavigationData& data)
{
  if (!data.currentRoomDetermined) {
    update_current(-1);
    update_presets({});

  } else {
    auto helper = RoomPresetHelper::instance;

    const auto& room = data.lab->getRoomFromId(data.currentRoom);
    const auto& presetList = helper->getPresetListByName(room.name, room.contents.contains("golden-door"));

    QVariantList presetsModel;
    int current = -1;

    if (!presetList.isEmpty()) {
      update_current(current);
      for (auto i = presetList.size() - 1; i >= 0; i--) {
        const auto& preset = presetList[i].second;
        QVariantMap item;
        item["areaCode"] = preset["areaCode"];
        item["doorExitLocations"] = helper->getDoorExitLocationModel(preset);
        item["contentLocations"] = helper->getContentLocationModel(preset);
        presetsModel.append(item);

        if (item["areaCode"].toString() == room.areaCode)
          current = presetList.size() - 1 - i;
      }

      presetsModel.append(QVariantMap {{"areaCode", "disabled"}, {"doorExitLocations", QVariantList {}}, {"contentLocations", QVariantList {}}});
      if (room.areaCode == "disabled")
        current = presetsModel.size() - 1;
    }

    update_current(current);
    update_presets(presetsModel);
  }
}
