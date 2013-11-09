#include "DefaultMessageHandler.h"

DefaultMessageHandler::DefaultMessageHandler(DHTMessageSender *sender) :
    DHTMessageHandler(sender)
{
}

//public
bool DefaultMessageHandler::handleResponse(const IPPort &src, const QMap<QByteArray, QSharedPointer<BencodeNode> > &responseArgs)
{

    return false;
}

//protected
bool DefaultMessageHandler::handlePing(const IPPort &src,
                                       const QMap<QByteArray, QSharedPointer<BencodeNode> > &queryArgs)
{

    return false;
}

//protected
bool DefaultMessageHandler::handleFindNode(const IPPort &src,
                                           const QMap<QByteArray, QSharedPointer<BencodeNode> > &queryArgs)
{

    return false;
}

//protected
bool DefaultMessageHandler::handleGetPeers(const IPPort &src,
                                           const QMap<QByteArray, QSharedPointer<BencodeNode> > &queryArgs)
{

    return false;
}

//protected
bool DefaultMessageHandler::handleAnnouncePeer(const IPPort &src,
                                               const QMap<QByteArray, QSharedPointer<BencodeNode> > &queryArgs)
{

    return false;
}
