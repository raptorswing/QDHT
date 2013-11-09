#ifndef DEFAULTMESSAGEHANDLER_H
#define DEFAULTMESSAGEHANDLER_H

#include "interfaces/DHTMessageHandler.h"
#include "IPPort.h"
#include "NodeID.h"

#include <QHash>
#include <QDateTime>

class DefaultMessageHandler : public DHTMessageHandler
{
public:
    DefaultMessageHandler(DHTMessageSender * sender, const NodeID& ourID);

protected:
    virtual bool _handlePing(const IPPort& src,
                             quint16 transactionID,
                             const NodeID& senderID);

    virtual bool _handleFindNode(const IPPort& src,
                                 quint16 transactionID,
                                 const NodeID& senderID,
                                 const NodeID& targetNode);

    virtual bool _handleGetPeers(const IPPort& src,
                                 quint16 transactionID,
                                 const NodeID& senderID,
                                 const NodeID& infoHash);

    virtual bool _handleAnnouncePeer(const IPPort& src,
                                     quint16 transactionID,
                                     const NodeID& senderID,
                                     const NodeID& infoHash,
                                     quint16 port,
                                     const QByteArray& token);

    virtual bool _handleResponse(const IPPort& src,
                                 quint16 transactionID,
                                 const NodeID& responderID,
                                 const QMap<QByteArray, QSharedPointer<BencodeNode> >& responseArgs);
};

#endif // DEFAULTMESSAGEHANDLER_H
