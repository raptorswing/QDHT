#include "QDHT.h"

#include <QtDebug>
#include <QDataStream>
#include <QTimer>
#include <QHostInfo>

#include "Bencode.h"
#include "BencodeNode.h"
#include "DictBencodeNode.h"
#include "BencodeNodeVisitor.h"

#include "DefaultMessageHandler.h"
#include "IPPort.h"

const QByteArray TRANS_ID_KEY = "t";

const QByteArray MSG_TYPE_KEY = "y";
const QByteArray QUERY_MSG_TYPE = "q";
const QByteArray RESPONSE_MSG_TYPE = "r";

const QByteArray QUERY_TYPE_KEY = "q";
const QByteArray QUERY_ARGS_KEY = "a";

const QByteArray RESPONSE_ARGS_KEY = "r";

QDHT::QDHT()
{
    _socket = new QUdpSocket(this);
    if (!_socket->bind(6881))
        qWarning() << "Failed to bind socket";
    else
        qDebug() << "Bound to" << _socket->localAddress() << _socket->localPort();

    connect(_socket,
            SIGNAL(readyRead()),
            this,
            SLOT(handleIncomingBytes()));

    QTimer::singleShot(1, this, SLOT(test()));

    //Add default msg handler
    QSharedPointer<DHTMessageHandler> handler(new DefaultMessageHandler(this, NodeID::GenerateFromBytes("testagmundo")));
    this->addMessageHandler(handler);
}

QDHT::~QDHT()
{

}

void QDHT::sendPing(const IPPort &dest, quint16 transactionID, const NodeID &myNodeID)
{
    QSharedPointer<DictBencodeNode> msg(new DictBencodeNode());

    //t - transactionID
    msg->insert(TRANS_ID_KEY, QDHT::transactionIDToBytes(transactionID));

    //y - "q" for "query"
    msg->insert(MSG_TYPE_KEY, "q");

    //q - "ping"
    msg->insert("q", "ping");

    QSharedPointer<DictBencodeNode> arguments(new DictBencodeNode());
    arguments->insert("id", myNodeID.bytes());

    msg->insert("a", arguments);

    const QByteArray bytes = Bencode::write(msg);
    _socket->writeDatagram(bytes, dest.host(), dest.port());
}

void QDHT::sendPong(const IPPort &dest, quint16 transactionID, const NodeID &myNodeID)
{
    QSharedPointer<DictBencodeNode> msg(new DictBencodeNode());

    //t - transactionID
    msg->insert(TRANS_ID_KEY, QDHT::transactionIDToBytes(transactionID));

    //y - "r" for "reply"
    msg->insert(MSG_TYPE_KEY, "r");

    QSharedPointer<DictBencodeNode> arguments(new DictBencodeNode());
    arguments->insert("id", myNodeID.bytes());

    msg->insert("r", arguments);

    const QByteArray bytes = Bencode::write(msg);
    _socket->writeDatagram(bytes, dest.host(), dest.port());
}

void QDHT::addMessageHandler(const QSharedPointer<DHTMessageHandler> &handler)
{
    _messageHandlers.append(handler);
}

void QDHT::test()
{
//    QHostInfo info = QHostInfo::fromName("router.bittorrent.com");
//    this->sendPing(info.addresses()[0], 6881, 500, NodeID::GenerateFromBytes("testamundo"));

    //this->sendPing(IPPort(QHostAddress("94.189.233.186"), 6881), 500, NodeID::GenerateFromBytes("testagmundo"));
    QByteArray test = QByteArray(20, (char)0);
    test[19] = 255;
    NodeID testNodeID = NodeID(test);

    qDebug() << testNodeID.toBigUint().ToString().c_str();
}

//private slot
void QDHT::handleIncomingBytes()
{
    while (_socket->hasPendingDatagrams())
    {
        const qint64 desiredBytes = _socket->pendingDatagramSize();
        QByteArray datagramBytes(desiredBytes, '0');

        QHostAddress srcIP;
        quint16 srcPort;

        const qint64 numBytesRead = _socket->readDatagram(datagramBytes.data(), desiredBytes, &srcIP, &srcPort);

        if (numBytesRead != desiredBytes)
        {
            qWarning() << "Failed to read correct number of datagram bytes!";
            continue;
        }

        this->beginProcessMessage(srcIP, srcPort, datagramBytes);
    }
}

//private slot
void QDHT::beginProcessMessage(const QHostAddress &srcIP, quint16 srcPort, const QByteArray &bytes)
{
    QSharedPointer<BencodeNode> parseTree = Bencode::parse(bytes);

    if (parseTree.isNull() || parseTree->type() != BencodeNode::DictNodeType)
    {
        qWarning() << "Bad parse from" << srcIP << srcPort << ":" << bytes;
        return;
    }

    QSharedPointer<DictBencodeNode> dict = parseTree.dynamicCast<DictBencodeNode>();
    if (dict.isNull())
    {
        qWarning() << "Cast Failure";
        return;
    }
    else if (!dict->containsKey(TRANS_ID_KEY) || !dict->containsKey(MSG_TYPE_KEY))
    {
        qWarning() << "Incomplete message";
        return;
    }

    QSharedPointer<ByteStringBencodeNode> transIDNode = dict->dict().value(TRANS_ID_KEY).dynamicCast<ByteStringBencodeNode>();
    QSharedPointer<ByteStringBencodeNode> msgTypeNode = dict->dict().value(MSG_TYPE_KEY).dynamicCast<ByteStringBencodeNode>();

    if (transIDNode.isNull() || msgTypeNode.isNull())
    {
        qWarning() << "Invalid transaction id node or invalid msg type node";
        return;
    }
    else if (transIDNode->byteString().size() != 2)
    {
        qWarning() << "Transaction ID must be two bytes only!";
        return;
    }
    else if (msgTypeNode->byteString().count() != 1)
    {
        qWarning() << "Msg type must be one byte only!";
        return;
    }

    const quint16 transactionID = QDHT::bytesToTransactionID(transIDNode->byteString());
    const char msgType = msgTypeNode->byteString().at(0);

    if (msgType == QUERY_MSG_TYPE.at(0) && dict->containsKey(QUERY_TYPE_KEY) && dict->containsKey(QUERY_ARGS_KEY))
    {
        qDebug() << "Got query";
        QSharedPointer<ByteStringBencodeNode> queryTypeNode = dict->dict().value(QUERY_TYPE_KEY).dynamicCast<ByteStringBencodeNode>();
        QSharedPointer<DictBencodeNode> queryArgsNode = dict->dict().value(QUERY_ARGS_KEY).dynamicCast<DictBencodeNode>();

        if (!queryArgsNode.isNull() && !queryTypeNode.isNull())
            this->beginProcessQuery(IPPort(srcIP, srcPort), transactionID, queryTypeNode->byteString(), queryArgsNode->dict());
        else
            qWarning() << "Query has no arguments";
    }
    else if (msgType == RESPONSE_MSG_TYPE.at(0) && dict->containsKey(RESPONSE_ARGS_KEY))
    {
        qDebug() << "Got response";
        QSharedPointer<DictBencodeNode> responseArgsNode = dict->dict().value(RESPONSE_ARGS_KEY).dynamicCast<DictBencodeNode>();
        if (!responseArgsNode.isNull())
            this->beginProcessResponse(IPPort(srcIP, srcPort), transactionID, responseArgsNode->dict());
        else
            qWarning() << "Response has no arguments";
    }
    else
    {
        qWarning() << "Unknown message type or invalid arguments" << msgType;
        return;
    }

    qDebug() << "Msg type:" << msgType << "Trans. ID:" << transactionID;

    {
        qDebug() << "Message from" << srcIP << srcPort;
        BencodeNodeVisitor * visitor = new BencodeNodeVisitor();
        parseTree->accept(visitor);
        delete visitor;
    }
}

//private slot
void QDHT::beginProcessQuery(const IPPort& src,
                             quint16 transactionID,
                             const QByteArray &queryType,
                             const QMap<QByteArray, QSharedPointer<BencodeNode> > &queryArgs)
{
    foreach(const QSharedPointer<DHTMessageHandler>& handler, _messageHandlers)
    {
        if (handler->handleQuery(src, transactionID, queryType, queryArgs))
            break;
    }
}

//private slot
void QDHT::beginProcessResponse(const IPPort& src,
                                quint16 transactionID,
                                const QMap<QByteArray,QSharedPointer<BencodeNode> > &responseArgs)
{
    foreach(const QSharedPointer<DHTMessageHandler>& handler, _messageHandlers)
    {
        if (handler->handleResponse(src, transactionID, responseArgs))
            break;
    }
}

//private static
QByteArray QDHT::transactionIDToBytes(quint16 transactionID)
{
    QByteArray toRet;
    QDataStream stream(&toRet, QIODevice::WriteOnly);

    stream << transactionID;
    return toRet;
}

//private static
quint16 QDHT::bytesToTransactionID(const QByteArray &transactionIDBytes)
{
    QDataStream stream(transactionIDBytes);

    quint16 toRet;
    stream >> toRet;
    return toRet;
}
