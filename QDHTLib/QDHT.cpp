#include "QDHT.h"

#include <QtDebug>
#include <QDataStream>
#include <QTimer>
#include <QHostInfo>

#include "Bencode.h"
#include "BencodeNode.h"
#include "DictBencodeNode.h"


QDHT::QDHT()
{
    _socket = new QUdpSocket(this);
    _socket->bind();

    qDebug() << "Bound to" << _socket->localAddress() << _socket->localPort();

    QTimer::singleShot(1, this, SLOT(test()));
}

void QDHT::sendPing(const QHostAddress &destHost, quint16 destPort, quint16 transactionID, const NodeID &myNodeID)
{
    QSharedPointer<DictBencodeNode> msg(new DictBencodeNode());

    //t - transactionID
    msg->insert("t", QDHT::transactionIDToBytes(transactionID));

    //y - "q" for "query"
    msg->insert("y", "q");

    //q - "ping"
    msg->insert("q", "ping");

    QSharedPointer<DictBencodeNode> arguments(new DictBencodeNode());
    arguments->insert("id", myNodeID.bytes());

    msg->insert("a", arguments);

    const QByteArray bytes = Bencode::write(msg);
    _socket->writeDatagram(bytes, destHost, destPort);
}

void QDHT::sendPong(const QHostAddress &destHost, quint16 destPort, quint16 transactionID, const NodeID &myNodeID)
{
    QSharedPointer<DictBencodeNode> msg(new DictBencodeNode());

    //t - transactionID
    msg->insert("t", QDHT::transactionIDToBytes(transactionID));

    //y - "r" for "reply"
    msg->insert("y", "r");

    QSharedPointer<DictBencodeNode> arguments(new DictBencodeNode());
    arguments->insert("id", myNodeID.bytes());

    msg->insert("r", arguments);

    const QByteArray bytes = Bencode::write(msg);
    _socket->writeDatagram(bytes, destHost, destPort);
}

void QDHT::test()
{
//    QHostInfo info = QHostInfo::fromName("router.bittorrent.com");
//    this->sendPing(info.addresses()[0], 6881, 500, NodeID::GenerateFromBytes("testamundo"));

    this->sendPing(QHostAddress("37.187.19.19"), 6881, 500, NodeID::GenerateFromBytes("testagmundo"));
}

//private static
QByteArray QDHT::transactionIDToBytes(quint16 transactionID)
{
    QByteArray toRet;
    QDataStream stream(&toRet, QIODevice::WriteOnly);

    stream << transactionID;
    return toRet;
}
