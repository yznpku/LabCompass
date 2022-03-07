#include "labyrinthmodelpropertiestest.h"
#include "model/labyrinthmodel.h"

LabyrinthModelPropertiesTest::LabyrinthModelPropertiesTest(QObject* parent)
    : QObject(parent)
{
}

void LabyrinthModelPropertiesTest::test_data()
{
    QTest::addColumn<QString>("fileName");
    QTest::addColumn<QString>("title");
    QTest::addColumn<QString>("difficulty");
    QTest::addColumn<QDate>("date");

    QTest::newRow("2018-01-09 Normal") << "2018-01-09_normal.json"
                                       << "2018-01-09 Normal"
                                       << "Normal" << QDate(2018, 1, 9);
    QTest::newRow("2018-01-09 Cruel") << "2018-01-09_cruel.json"
                                      << "2018-01-09 Cruel"
                                      << "Cruel" << QDate(2018, 1, 9);
    QTest::newRow("2018-01-09 Merciless") << "2018-01-09_merciless.json"
                                          << "2018-01-09 Merciless"
                                          << "Merciless" << QDate(2018, 1, 9);
    QTest::newRow("2018-01-09 Uber") << "2018-01-09_uber.json"
                                     << "2018-01-09 Uber"
                                     << "Uber" << QDate(2018, 1, 9);
    QTest::newRow("2018-01-10 Normal") << "2018-01-10_normal.json"
                                       << "2018-01-10 Normal"
                                       << "Normal" << QDate(2018, 1, 10);
    QTest::newRow("2018-01-10 Cruel") << "2018-01-10_cruel.json"
                                      << "2018-01-10 Cruel"
                                      << "Cruel" << QDate(2018, 1, 10);
    QTest::newRow("2018-01-10 Merciless") << "2018-01-10_merciless.json"
                                          << "2018-01-10 Merciless"
                                          << "Merciless" << QDate(2018, 1, 10);
    QTest::newRow("2018-01-10 Uber") << "2018-01-10_uber.json"
                                     << "2018-01-10 Uber"
                                     << "Uber" << QDate(2018, 1, 10);
}

void LabyrinthModelPropertiesTest::test()
{
    QFETCH(QString, fileName);

    LabyrinthData data;
    data.loadFromFile(QDir("data").filePath(fileName));
    LabyrinthModel model;
    model.loadFromData(data);

    QFETCH(QString, title);
    QCOMPARE(model.get_title(), title);

    QFETCH(QString, difficulty);
    QCOMPARE(model.get_difficulty(), difficulty);

    QFETCH(QDate, date);
    QCOMPARE(model.get_date(), date);
}
