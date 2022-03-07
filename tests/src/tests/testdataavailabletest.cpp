#include "testdataavailabletest.h"

TestDataAvailableTest::TestDataAvailableTest(QObject* parent)
    : QObject(parent)
{
}

void TestDataAvailableTest::test_data()
{
    QTest::addColumn<QString>("fileName");

    QTest::newRow("2018-01-09_normal.json") << "2018-01-09_normal.json";
    QTest::newRow("2018-01-09_cruel.json") << "2018-01-09_cruel.json";
    QTest::newRow("2018-01-09_merciless.json") << "2018-01-09_merciless.json";
    QTest::newRow("2018-01-09_uber.json") << "2018-01-09_uber.json";
    QTest::newRow("2018-01-10_normal.json") << "2018-01-10_normal.json";
    QTest::newRow("2018-01-10_cruel.json") << "2018-01-10_cruel.json";
    QTest::newRow("2018-01-10_merciless.json") << "2018-01-10_merciless.json";
    QTest::newRow("2018-01-10_uber.json") << "2018-01-10_uber.json";
}

void TestDataAvailableTest::test()
{
    QFETCH(QString, fileName);
    QVERIFY2(QDir("data").exists(fileName), "Test data not found. Run \"make install\" before running this test.");
}
