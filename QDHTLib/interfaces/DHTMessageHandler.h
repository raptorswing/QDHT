#ifndef DHTMESSAGEHANDLER_H
#define DHTMESSAGEHANDLER_H

#include "DHTMessageSender.h"
#include "BencodeNode.h"
#include "IPPort.h"

class DHTMessageHandler
{
public:
    DHTMessageHandler(DHTMessageSender * sender);
    virtual ~DHTMessageHandler();

    virtual bool handleQuery(const IPPort& src,
                             const QByteArray& queryType,
                             const QMap<QByteArray, QSharedPointer<BencodeNode> > &queryArgs);

    virtual bool handleResponse(const IPPort& src,
                                const QMap<QByteArray,QSharedPointer<BencodeNode> > &responseArgs);

protected:
    virtual bool handlePing(const IPPort& src,
                            const QMap<QByteArray, QSharedPointer<BencodeNode> >& queryArgs);

    virtual bool handleFindNode(const IPPort& src,
                                const QMap<QByteArray, QSharedPointer<BencodeNode> >& queryArgs);

    virtual bool handleGetPeers(const IPPort& src,
                                const QMap<QByteArray, QSharedPointer<BencodeNode> >& queryArgs);

    virtual bool handleAnnouncePeer(const IPPort& src,
                                    const QMap<QByteArray, QSharedPointer<BencodeNode> >& queryArgs);

    DHTMessageSender * sender() const;

private:
    DHTMessageSender * _sender;
};

#endif // DHTMESSAGEHANDLER_H
