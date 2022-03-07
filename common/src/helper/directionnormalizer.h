#ifndef DIRECTIONNORMALIZER_H
#define DIRECTIONNORMALIZER_H

#include "Hungarian.h"
#include "global.h"

class DirectionNormalizer {
    struct ConnectionDetails {
        QList<RoomId> rooms;
        QList<RoomId> unknownDirectionRooms;
        QList<RoomId> secretPassageRooms;
        QList<std::pair<DirectionCode, RoomId>> regularDirectionRooms;
    };

    HungarianAlgorithm hungarian;

public:
    DirectionNormalizer();

    RoomConnections normalize(const RoomConnections& original, const QList<DirectionCode>& pattern);

private:
    ConnectionDetails breakdownConnections(const RoomConnections& connections);
    RoomConnections reconstructConnections(const ConnectionDetails& breakdown);
    qreal costBetweenDirections(const DirectionCode& d1, const DirectionCode& d2);
};

#endif // DIRECTIONNORMALIZER_H
