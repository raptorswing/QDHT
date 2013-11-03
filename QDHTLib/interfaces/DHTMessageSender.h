#ifndef DHTMESSAGESENDER_H
#define DHTMESSAGESENDER_H

#include <QHostAddress>

#include "NodeID.h"

class DHTMessageSender
{
public:
    DHTMessageSender();
    virtual ~DHTMessageSender();

    virtual void sendPing(const QHostAddress& destHost,
                  quint16 destPort,
                  quint16 transactionID,
                  const NodeID& myNodeID) =0;

    virtual void sendPong(const QHostAddress& destHost,
                  quint16 destPort,
                  quint16 transactionID,
                  const NodeID& myNodeID) =0;
};

#endif // DHTMESSAGESENDER_H
