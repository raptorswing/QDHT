#include "DHTMessageHandler.h"

DHTMessageHandler::DHTMessageHandler(DHTMessageSender *sender) : _sender(sender)
{
}

//virtual
DHTMessageHandler::~DHTMessageHandler()
{
}

bool DHTMessageHandler::handleQuery(const IPPort &src,
                                    const QByteArray &queryType,
                                    const QMap<QByteArray, QSharedPointer<BencodeNode> > &queryArgs)
{
    if (queryType == "ping")
        return this->handlePing(src, queryArgs);
    else if (queryType == "find_node")
        return this->handleFindNode(src, queryArgs);
    else if (queryType == "get_peers")
        return this->handleGetPeers(src, queryArgs);
    else if (queryType == "announce_peer")
        return this->handleAnnouncePeer(src, queryArgs);
    else
    {
        qWarning() << "Unknown query type" << queryType;
        return false;
    }
}

bool DHTMessageHandler::handleResponse(const IPPort &src, const QMap<QByteArray, QSharedPointer<BencodeNode> > &responseArgs)
{
    Q_UNUSED(src)
    Q_UNUSED(responseArgs)
    return false;
}

//protected
bool DHTMessageHandler::handlePing(const IPPort &src, const QMap<QByteArray, QSharedPointer<BencodeNode> > &queryArgs)
{
    Q_UNUSED(src)
    Q_UNUSED(queryArgs)
    return false;
}

//protected
bool DHTMessageHandler::handleFindNode(const IPPort &src, const QMap<QByteArray, QSharedPointer<BencodeNode> > &queryArgs)
{
    Q_UNUSED(src)
    Q_UNUSED(queryArgs)
    return false;
}

//protected
bool DHTMessageHandler::handleGetPeers(const IPPort &src, const QMap<QByteArray, QSharedPointer<BencodeNode> > &queryArgs)
{
    Q_UNUSED(src)
    Q_UNUSED(queryArgs)
    return false;
}

//protected
bool DHTMessageHandler::handleAnnouncePeer(const IPPort &src, const QMap<QByteArray, QSharedPointer<BencodeNode> > &queryArgs)
{
    Q_UNUSED(src)
    Q_UNUSED(queryArgs)
    return false;
}

//protected
DHTMessageSender *DHTMessageHandler::sender() const
{
    return _sender;
}
