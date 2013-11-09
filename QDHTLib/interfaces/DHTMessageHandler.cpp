#include "DHTMessageHandler.h"

#include "ByteStringBencodeNode.h"
#include "IntegerBencodeNode.h"

DHTMessageHandler::DHTMessageHandler(DHTMessageSender *sender, const NodeID &ourID) : _sender(sender), _ourID(ourID)
{
}

//virtual
DHTMessageHandler::~DHTMessageHandler()
{
}

bool DHTMessageHandler::handleQuery(const IPPort &src,
                                    quint16 transactionID,
                                    const QByteArray &queryType,
                                    const QMap<QByteArray, QSharedPointer<BencodeNode> > &queryArgs)
{
    //Get the querying node's ID
    const NodeID senderID = DHTMessageHandler::extractByteStringArg(queryArgs, "id");
    if (senderID.isNull())
    {
        qDebug() << "Didn't receive querying ID in query";
        return false;
    }

    //Update our "known hosts" data structure
    this->updateKnownHosts(senderID, src);



    if (queryType == "ping")
        return this->handlePing(src, transactionID, senderID, queryArgs);
    else if (queryType == "find_node")
        return this->handleFindNode(src, transactionID, senderID, queryArgs);
    else if (queryType == "get_peers")
        return this->handleGetPeers(src, transactionID, senderID, queryArgs);
    else if (queryType == "announce_peer")
        return this->handleAnnouncePeer(src, transactionID, senderID, queryArgs);
    else
    {
        qDebug() << "Unknown query type" << queryType;
        return false;
    }
}

bool DHTMessageHandler::handleResponse(const IPPort &src,
                                       quint16 transactionID,
                                       const QMap<QByteArray, QSharedPointer<BencodeNode> > &responseArgs)
{
    const NodeID responderID = DHTMessageHandler::extractByteStringArg(responseArgs, "id");
    if (responderID.isNull())
    {
        qDebug() << "Didn't receive responder's ID in response";
        return false;
    }

    this->updateKnownHosts(responderID, src);

    return this->_handleResponse(src, transactionID, responderID, responseArgs);
}

//protected
bool DHTMessageHandler::handlePing(const IPPort &src,
                                   quint16 transactionID,
                                   const NodeID &senderID,
                                   const QMap<QByteArray, QSharedPointer<BencodeNode> > &queryArgs)
{
    Q_UNUSED(queryArgs)

    return this->_handlePing(src, transactionID, senderID);
}

//protected
bool DHTMessageHandler::handleFindNode(const IPPort &src,
                                       quint16 transactionID,
                                       const NodeID& senderID,
                                       const QMap<QByteArray, QSharedPointer<BencodeNode> > &queryArgs)
{
    //Get the target Node ID
    const NodeID targetNodeID = DHTMessageHandler::extractByteStringArg(queryArgs, "target");
    if (targetNodeID.isNull())
    {
        qDebug() << "Received find_node with no target";
        return false;
    }

    return this->_handleFindNode(src, transactionID, senderID, targetNodeID);
}

//protected
bool DHTMessageHandler::handleGetPeers(const IPPort &src,
                                       quint16 transactionID,
                                       const NodeID& senderID,
                                       const QMap<QByteArray, QSharedPointer<BencodeNode> > &queryArgs)
{
    //Get the target info hash
    const NodeID infoHash = DHTMessageHandler::extractByteStringArg(queryArgs, "info_hash");
    if (infoHash.isNull())
    {
        qDebug() << "Received get_peers with no info hash";
        return false;
    }

    return this->_handleGetPeers(src, transactionID, senderID, infoHash);
}

//protected
bool DHTMessageHandler::handleAnnouncePeer(const IPPort &src,
                                           quint16 transactionID,
                                           const NodeID &senderID,
                                           const QMap<QByteArray, QSharedPointer<BencodeNode> > &queryArgs)
{
    //Get the info hash they're announcing
    const NodeID infoHash = DHTMessageHandler::extractByteStringArg(queryArgs, "info_hash");
    if (infoHash.isNull())
    {
        qDebug() << "Received announce_peer with no info hash";
        return false;
    }

    //Get their port number
    bool ok;
    const qint64 portNum = DHTMessageHandler::extractIntegerArg(queryArgs, "port", ok);
    if (!ok || portNum < 0 || portNum >= 65536)
    {
        qDebug() << "Received announce_peer with missing or invalid port";
        return false;
    }

    //Get the token
    const QByteArray token = DHTMessageHandler::extractByteStringArg(queryArgs, "token");
    if (token.isNull())
    {
        qDebug() << "Received announce_peer with no token";
        return false;
    }

    //TODO - Handle implied port
    if (queryArgs.contains("implied_port"))
    {
        qDebug() << "Implied port is type" << queryArgs.value("implied_port")->type();
    }

    return this->_handleAnnouncePeer(src, transactionID, senderID, infoHash, portNum, token);
}

bool DHTMessageHandler::_handlePing(const IPPort &src,
                                    quint16 transactionID,
                                    const NodeID &senderID)
{
    Q_UNUSED(src)
    Q_UNUSED(transactionID)
    Q_UNUSED(senderID)

    //Base implementation is no-op
    return false;
}

bool DHTMessageHandler::_handleFindNode(const IPPort &src,
                                        quint16 transactionID,
                                        const NodeID &senderID,
                                        const NodeID &targetNode)
{
    Q_UNUSED(src)
    Q_UNUSED(transactionID)
    Q_UNUSED(senderID)
    Q_UNUSED(targetNode)

    //Base implementation is no-op
    return false;
}

bool DHTMessageHandler::_handleGetPeers(const IPPort &src,
                                        quint16 transactionID,
                                        const NodeID &senderID,
                                        const NodeID &infoHash)
{
    Q_UNUSED(src)
    Q_UNUSED(transactionID)
    Q_UNUSED(senderID)
    Q_UNUSED(infoHash)

    //Base implementation is no-op
    return false;
}

bool DHTMessageHandler::_handleAnnouncePeer(const IPPort &src,
                                            quint16 transactionID,
                                            const NodeID &senderID,
                                            const NodeID &infoHash,
                                            quint16 port,
                                            const QByteArray &token)
{
    Q_UNUSED(src)
    Q_UNUSED(transactionID)
    Q_UNUSED(senderID)
    Q_UNUSED(infoHash)
    Q_UNUSED(port)
    Q_UNUSED(token)

    //Base implementation is no-op
    return false;
}

//protected
bool DHTMessageHandler::_handleResponse(const IPPort &src,
                                        quint16 transactionID,
                                        const NodeID &responderID,
                                        const QMap<QByteArray, QSharedPointer<BencodeNode> > &responseArgs)
{
    Q_UNUSED(src);
    Q_UNUSED(transactionID)
    Q_UNUSED(responderID)
    Q_UNUSED(responseArgs)

    //Base implementation is no-op
    return false;
}

//protected
DHTMessageSender *DHTMessageHandler::sender() const
{
    return _sender;
}

//protected
const NodeID &DHTMessageHandler::ourID() const
{
    return _ourID;
}

//protected
void DHTMessageHandler::updateKnownHosts(const NodeID &node, const IPPort &host)
{
    _knownNodes.insert(node, QDateTime::currentDateTime());
    _nodeHosts.insert(node, host);
}

//protected static
QByteArray DHTMessageHandler::extractByteStringArg(const QMap<QByteArray, QSharedPointer<BencodeNode> > &args,
                                                   const QByteArray &argName)
{
    QByteArray toRet;

    if (args.contains(argName) && args.value(argName)->type() == BencodeNode::ByteStringNodeType)
    {
        QSharedPointer<ByteStringBencodeNode> castedNode = args.value(argName).dynamicCast<ByteStringBencodeNode>();

        if (!castedNode.isNull())
            toRet = castedNode->byteString();
    }


    return toRet;
}

//protected static
qint64 DHTMessageHandler::extractIntegerArg(const QMap<QByteArray, QSharedPointer<BencodeNode> > &args,
                                            const QByteArray &argName,
                                            bool& ok)
{
    qint64 toRet;
    ok = false;

    if (args.contains(argName) && args.value(argName)->type() == BencodeNode::IntegerNodeType)
    {
        QSharedPointer<IntegerBencodeNode> castedNode = args.value(argName).dynamicCast<IntegerBencodeNode>();

        if (!castedNode.isNull())
        {
            toRet = castedNode->num();
            ok = true;
        }
    }
    return toRet;
}
