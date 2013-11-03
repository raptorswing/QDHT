#include "QDHT.h"

#include <QtDebug>
#include <QDataStream>

#include "Bencode.h"
#include "BencodeNode.h"
#include "DictBencodeNode.h"


QDHT::QDHT()
{
    _socket = new QUdpSocket(this);
    _socket->bind();

    qDebug() << "Bound to" << _socket->localAddress() << _socket->localPort();
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
    qDebug() << bytes;
}

//private static
QByteArray QDHT::transactionIDToBytes(quint16 transactionID)
{
    QByteArray toRet;
    QDataStream stream(&toRet, QIODevice::WriteOnly);

    stream << transactionID;
    return toRet;
}
