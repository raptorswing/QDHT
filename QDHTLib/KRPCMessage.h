#ifndef KRPCMESSAGE_H
#define KRPCMESSAGE_H

#include "NodeID.h"
#include "BencodeNode.h"

#include <QSharedPointer>

class KRPCMessage
{
public:
    enum KRPCMessageType
    {
        QueryMessage,
        ResponseMessage,
        ErrorMessage
    };

    enum KRPCQueryType
    {
        PingQuery,
        FindNodeQuery,
        GetPeersQuery,
        AnnouncePeerQuery
    };

public:
    KRPCMessage();

    KRPCMessageType messageType;

    KRPCQueryType queryType; //Only used for queries

    NodeID nodeID;

    QSharedPointer<BencodeNode> payload;
};

#endif // KRPCMESSAGE_H
