#ifndef DHTMESSAGESENDER_H
#define DHTMESSAGESENDER_H

#include <QHostAddress>

#include "NodeID.h"
#include "IPPort.h"

class DHTMessageSender
{
public:
    DHTMessageSender();
    virtual ~DHTMessageSender();

    virtual void sendPing(const IPPort& dest,
                  quint16 transactionID,
                  const NodeID& myNodeID) =0;

    virtual void sendPong(const IPPort& dest,
                  quint16 transactionID,
                  const NodeID& myNodeID) =0;
};

#endif // DHTMESSAGESENDER_H
