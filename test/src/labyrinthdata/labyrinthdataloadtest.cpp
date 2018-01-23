#include "labyrinthdataloadtest.h"
#include "model/labyrinthdata.h"

LabyrinthDataLoadTest::LabyrinthDataLoadTest(QObject *parent) : QObject(parent)
{

}

void LabyrinthDataLoadTest::testLoad_data()
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

void LabyrinthDataLoadTest::testLoad()
{
  QFETCH(QString, fileName);
  LabyrinthData data;
  QVERIFY(data.loadFromFile(QDir("data").filePath(fileName)));
}
