#ifndef DEFAULTMESSAGEHANDLER_H
#define DEFAULTMESSAGEHANDLER_H

#include "interfaces/DHTMessageHandler.h"
#include "IPPort.h"

class DefaultMessageHandler : public DHTMessageHandler
{
public:
    DefaultMessageHandler(DHTMessageSender * sender);


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
};

#endif // DEFAULTMESSAGEHANDLER_H
