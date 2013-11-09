#ifndef DHTMESSAGEHANDLER_H
#define DHTMESSAGEHANDLER_H

#include "DHTMessageSender.h"
#include "BencodeNode.h"
#include "IPPort.h"
#include "NodeID.h"

#include <QHash>
#include <QDateTime>

class DHTMessageHandler
{
public:
    DHTMessageHandler(DHTMessageSender * sender, const NodeID& ourID);
    virtual ~DHTMessageHandler();

    bool handleQuery(const IPPort& src,
                     quint16 transactionID,
                     const QByteArray& queryType,
                     const QMap<QByteArray, QSharedPointer<BencodeNode> > &queryArgs);

    bool handleResponse(const IPPort& src,
                        quint16 transactionID,
                        const QMap<QByteArray,QSharedPointer<BencodeNode> > &responseArgs);



protected:
    bool handlePing(const IPPort& src,
                    quint16 transactionID,
                    const NodeID& senderID,
                    const QMap<QByteArray, QSharedPointer<BencodeNode> >& queryArgs);

    bool handleFindNode(const IPPort& src,
                        quint16 transactionID,
                        const NodeID& senderID,
                        const QMap<QByteArray, QSharedPointer<BencodeNode> >& queryArgs);

    bool handleGetPeers(const IPPort& src,
                        quint16 transactionID,
                        const NodeID& senderID,
                        const QMap<QByteArray, QSharedPointer<BencodeNode> >& queryArgs);

    bool handleAnnouncePeer(const IPPort& src,
                            quint16 transactionID,
                            const NodeID& senderID,
                            const QMap<QByteArray, QSharedPointer<BencodeNode> >& queryArgs);

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

    DHTMessageSender * sender() const;

    const NodeID& ourID() const;

    void updateKnownHosts(const NodeID &node, const IPPort& host);

    static QByteArray extractByteStringArg(const QMap<QByteArray, QSharedPointer<BencodeNode> >& args,
                                           const QByteArray& argName);

    static qint64 extractIntegerArg(const QMap<QByteArray, QSharedPointer<BencodeNode> >& args,
                                    const QByteArray& argName,
                                    bool& ok);

private:
    DHTMessageSender * _sender;
    NodeID _ourID;

    QHash<NodeID, QDateTime> _knownNodes;
    QHash<NodeID, IPPort> _nodeHosts;
};

#endif // DHTMESSAGEHANDLER_H
