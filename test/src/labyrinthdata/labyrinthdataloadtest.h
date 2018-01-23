#ifndef LABYRINTHMODELLOADTEST_H
#define LABYRINTHMODELLOADTEST_H

#include <QtTest>

class LabyrinthDataLoadTest : public QObject
{
  Q_OBJECT
public:
  explicit LabyrinthDataLoadTest(QObject *parent = nullptr);
private slots:
  void testLoad_data();
  void testLoad();
};

#endif // LABYRINTHMODELLOADTEST_H
