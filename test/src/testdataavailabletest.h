#ifndef TESTDATAAVAILABLETEST_H
#define TESTDATAAVAILABLETEST_H

#include <QtTest>

class TestDataAvailableTest : public QObject
{
  Q_OBJECT
public:
  explicit TestDataAvailableTest(QObject *parent = nullptr);
private slots:
  void testTestDataAvailable_data();
  void testTestDataAvailable();
};

#endif // TESTDATAAVAILABLETEST_H
