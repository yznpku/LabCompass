#ifndef LABYRINTHDATAROOMISTRIALTEST_H
#define LABYRINTHDATAROOMISTRIALTEST_H

#include <QtTest>

class LabyrinthDataRoomIsTrialTest : public QObject {
    Q_OBJECT

public:
    LabyrinthDataRoomIsTrialTest(QObject* parent = nullptr);

private slots:
    void test_data();
    void test();
};

#endif // LABYRINTHDATAROOMISTRIALTEST_H
