#ifndef DHTMESSAGEHANDLER_H
#define DHTMESSAGEHANDLER_H

#include "DHTMessageSender.h"
#include "BencodeNode.h"

class DHTMessageHandler
{
public:
    DHTMessageHandler(DHTMessageSender * sender);
    virtual ~DHTMessageHandler();

    virtual bool handleQuery(const QHostAddress& srcIP,
                             quint16 srcPort,
                             const QByteArray& queryType,
                             const QMap<QByteArray, QSharedPointer<BencodeNode> > &queryArgs);

    virtual bool handleResponse(const QHostAddress &srcIP,
                                quint16 srcPort,
                                const QMap<QByteArray,QSharedPointer<BencodeNode> > &responseArgs);

protected:
    virtual bool handlePing(const QHostAddress& srcIP,
                            quint16 srcPort,
                            const QMap<QByteArray, QSharedPointer<BencodeNode> >& queryArgs);

    virtual bool handleFindNode(const QHostAddress& srcIP,
                                quint16 srcPort,
                                const QMap<QByteArray, QSharedPointer<BencodeNode> >& queryArgs);

    virtual bool handleGetPeers(const QHostAddress& srcIP,
                                quint16 srcPort,
                                const QMap<QByteArray, QSharedPointer<BencodeNode> >& queryArgs);

    virtual bool handleAnnouncePeer(const QHostAddress& srcIP,
                                    quint16 srcPort,
                                    const QMap<QByteArray, QSharedPointer<BencodeNode> >& queryArgs);

    DHTMessageSender * sender() const;

private:
    DHTMessageSender * _sender;
};

#endif // DHTMESSAGEHANDLER_H
