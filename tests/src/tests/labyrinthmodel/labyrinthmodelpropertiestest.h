#ifndef LABYRINTHMODELPROPERTIESTEST_H
#define LABYRINTHMODELPROPERTIESTEST_H

#include <QtTest>

class LabyrinthModelPropertiesTest : public QObject {
    Q_OBJECT

public:
    LabyrinthModelPropertiesTest(QObject* parent = nullptr);

private slots:
    void test_data();
    void test();
};

#endif // LABYRINTHMODELPROPERTIESTEST_H
