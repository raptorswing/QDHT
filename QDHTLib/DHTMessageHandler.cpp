#include "DHTMessageHandler.h"

DHTMessageHandler::DHTMessageHandler(DHTMessageSender *sender) : _sender(sender)
{
}

//virtual
DHTMessageHandler::~DHTMessageHandler()
{
}

bool DHTMessageHandler::handleQuery(const QHostAddress &srcIP,
                                    quint16 srcPort,
                                    const QByteArray &queryType,
                                    const QMap<QByteArray, QSharedPointer<BencodeNode> > &queryArgs)
{
    if (queryType == "ping")
        return this->handlePing(srcIP, srcPort, queryArgs);
    else if (queryType == "find_node")
        return this->handleFindNode(srcIP, srcPort, queryArgs);
    else if (queryType == "get_peers")
        return this->handleGetPeers(srcIP, srcPort, queryArgs);
    else if (queryType == "announce_peer")
        return this->handleAnnouncePeer(srcIP, srcPort, queryArgs);
    else
    {
        qWarning() << "Unknown query type" << queryType;
        return false;
    }
}

bool DHTMessageHandler::handleResponse(const QHostAddress &srcIP, quint16 srcPort, const QMap<QByteArray, QSharedPointer<BencodeNode> > &responseArgs)
{
    Q_UNUSED(srcIP)
    Q_UNUSED(srcPort)
    Q_UNUSED(responseArgs)
    return false;
}

//protected
bool DHTMessageHandler::handlePing(const QHostAddress &srcIP, quint16 srcPort, const QMap<QByteArray, QSharedPointer<BencodeNode> > &queryArgs)
{
    Q_UNUSED(srcIP)
    Q_UNUSED(srcPort)
    Q_UNUSED(queryArgs)
    return false;
}

//protected
bool DHTMessageHandler::handleFindNode(const QHostAddress &srcIP, quint16 srcPort, const QMap<QByteArray, QSharedPointer<BencodeNode> > &queryArgs)
{
    Q_UNUSED(srcIP)
    Q_UNUSED(srcPort)
    Q_UNUSED(queryArgs)
    return false;
}

//protected
bool DHTMessageHandler::handleGetPeers(const QHostAddress &srcIP, quint16 srcPort, const QMap<QByteArray, QSharedPointer<BencodeNode> > &queryArgs)
{
    Q_UNUSED(srcIP)
    Q_UNUSED(srcPort)
    Q_UNUSED(queryArgs)
    return false;
}

//protected
bool DHTMessageHandler::handleAnnouncePeer(const QHostAddress &srcIP, quint16 srcPort, const QMap<QByteArray, QSharedPointer<BencodeNode> > &queryArgs)
{
    Q_UNUSED(srcIP)
    Q_UNUSED(srcPort)
    Q_UNUSED(queryArgs)
    return false;
}

//protected
DHTMessageSender *DHTMessageHandler::sender() const
{
    return _sender;
}
