#include "helper/roompresethelper.h"
#include "tests/labyrinthdata/labyrinthdataloadtest.h"
#include "tests/labyrinthdata/labyrinthdataroomistrialtest.h"
#include "tests/labyrinthmodel/labyrinthmodelpropertiestest.h"
#include "tests/testdataavailabletest.h"
#include <QtTest>
#include <memory>

int main(int argc, char** argv)
{
    Q_INIT_RESOURCE(common);
    RoomPresetHelper::instance = new RoomPresetHelper();

    if (int r = QTest::qExec(std::make_unique<TestDataAvailableTest>().get())) {
        return r;
    }

    QTest::qExec(std::make_unique<LabyrinthDataLoadTest>().get());
    QTest::qExec(std::make_unique<LabyrinthDataRoomIsTrialTest>().get());
    QTest::qExec(std::make_unique<LabyrinthModelPropertiesTest>().get());
    return 0;
}
