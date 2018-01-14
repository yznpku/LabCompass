#include <QtTest>
#include <memory>
#include "testdataavailabletest.h"
#include "labyrinthdata/labyrinthdataloadtest.h"

int main()
{
  if (int r = QTest::qExec(std::make_unique<TestDataAvailableTest>().get()))
    return r;

  QTest::qExec(std::make_unique<LabyrinthDataLoadTest>().get());
  return 0;
}
