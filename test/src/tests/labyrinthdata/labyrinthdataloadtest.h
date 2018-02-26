#ifndef LABYRINTHMODELLOADTEST_H
#define LABYRINTHMODELLOADTEST_H

#include <QtTest>

class LabyrinthDataLoadTest : public QObject
{
  Q_OBJECT

public:
  explicit LabyrinthDataLoadTest(QObject *parent = nullptr);

private slots:
  void test_data();
  void test();
};

#endif // LABYRINTHMODELLOADTEST_H
