#include <QtTest>
#include <memory>
#include "tests/testdataavailabletest.h"
#include "tests/labyrinthdata/labyrinthdataloadtest.h"
#include "tests/labyrinthmodel/labyrinthmodelpropertiestest.h"

int main()
{
  if (int r = QTest::qExec(std::make_unique<TestDataAvailableTest>().get()))
    return r;

  QTest::qExec(std::make_unique<LabyrinthDataLoadTest>().get());
  QTest::qExec(std::make_unique<LabyrinthModelPropertiesTest>().get());
  return 0;
}
