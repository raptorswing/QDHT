#ifndef QDHT_H
#define QDHT_H

#include "qdhtlib_global.h"

#include "NodeID.h"

#include "DictBencodeNode.h"

#include <QHostAddress>
#include <QUdpSocket>
#include <QObject>


class QDHTLIBSHARED_EXPORT QDHT : public QObject
{
    Q_OBJECT
public:
    QDHT();

    void sendPing(const QHostAddress& destHost,
                  quint16 destPort,
                  quint16 transactionID,
                  const NodeID& myNodeID);

    void sendPong(const QHostAddress& destHost,
                  quint16 destPort,
                  quint16 transactionID,
                  const NodeID& myNodeID);

signals:


public slots:
    void test();

private slots:
    void handleIncomingBytes();
    void beginProcessMessage(const QHostAddress& srcIP, quint16 srcPort, const QByteArray& bytes);

    void beginProcessQuery(const QHostAddress& srcIP,
                           quint16 srcPort,
                           const QByteArray& queryType,
                           const QMap<QByteArray, QSharedPointer<BencodeNode> >& queryArgs);

    void beginProcessResponse(const QHostAddress& srcIP, quint16 srcPort,
                              const QMap<QByteArray, QSharedPointer<BencodeNode> >& responseArgs);

private:
    static QByteArray transactionIDToBytes(quint16 transactionID);
    static quint16 bytesToTransactionID(const QByteArray& transactionIDBytes);
    QUdpSocket * _socket;
};

#endif // QDHT_H
