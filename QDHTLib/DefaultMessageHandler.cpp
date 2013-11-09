#include "DefaultMessageHandler.h"

DefaultMessageHandler::DefaultMessageHandler(DHTMessageSender *sender, const NodeID &ourID) :
    DHTMessageHandler(sender, ourID)
{
}

bool DefaultMessageHandler::_handlePing(const IPPort &src,
                                        quint16 transactionID,
                                        const NodeID &senderID)
{
    Q_UNUSED(senderID)

    //Respond with appropriate pong
    this->sender()->sendPong(src, transactionID, this->ourID());

    return true;
}

bool DefaultMessageHandler::_handleFindNode(const IPPort &src,
                                            quint16 transactionID,
                                            const NodeID &senderID,
                                            const NodeID &targetNode)
{
    return false;
}

bool DefaultMessageHandler::_handleGetPeers(const IPPort &src,
                                            quint16 transactionID,
                                            const NodeID &senderID,
                                            const NodeID &infoHash)
{
    return false;
}

bool DefaultMessageHandler::_handleAnnouncePeer(const IPPort &src,
                                                quint16 transactionID,
                                                const NodeID &senderID,
                                                const NodeID &infoHash,
                                                quint16 port,
                                                const QByteArray &token)
{
    return false;
}

bool DefaultMessageHandler::_handleResponse(const IPPort &src,
                                            quint16 transactionID,
                                            const NodeID &responderID,
                                            const QMap<QByteArray, QSharedPointer<BencodeNode> > &responseArgs)
{
    return false;
}
