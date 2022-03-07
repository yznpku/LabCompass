#include "labyrinthdataroomistrialtest.h"
#include "model/labyrinthdata.h"

using Set = QSet<QString>;

LabyrinthDataRoomIsTrialTest::LabyrinthDataRoomIsTrialTest(QObject* parent)
    : QObject(parent)
{
}

void LabyrinthDataRoomIsTrialTest::test_data()
{
    QTest::addColumn<QString>("fileName");
    QTest::addColumn<Set>("trials");

    QTest::newRow("2018-01-09 Normal") << "2018-01-09_normal.json"
                                       << Set { "2", "4", "9" };
    QTest::newRow("2018-01-09 Cruel") << "2018-01-09_cruel.json"
                                      << Set { "2", "7", "12" };
    QTest::newRow("2018-01-09 Merciless") << "2018-01-09_merciless.json"
                                          << Set { "4", "7", "13" };
    QTest::newRow("2018-01-09 Uber") << "2018-01-09_uber.json"
                                     << Set { "4", "10", "15" };
    QTest::newRow("2018-01-10 Normal") << "2018-01-10_normal.json"
                                       << Set { "2", "4", "10" };
    QTest::newRow("2018-01-10 Cruel") << "2018-01-10_cruel.json"
                                      << Set { "3", "7", "11" };
    QTest::newRow("2018-01-10 Merciless") << "2018-01-10_merciless.json"
                                          << Set { "4", "7", "12" };
    QTest::newRow("2018-01-10 Uber") << "2018-01-10_uber.json"
                                     << Set { "5", "10", "15" };
}

void LabyrinthDataRoomIsTrialTest::test()
{
    QFETCH(QString, fileName);
    LabyrinthData data;
    data.loadFromFile(QDir("data").filePath(fileName));

    QFETCH(Set, trials);
    Set actualTrials;
    for (auto i = data.rooms.begin(); i != data.rooms.end(); i++)
        if (data.roomIsTrial(i->id))
            actualTrials.insert(i->id);
    QCOMPARE(actualTrials, trials);
}
