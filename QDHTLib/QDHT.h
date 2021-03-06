#ifndef QDHT_H
#define QDHT_H

#include "qdhtlib_global.h"

#include "NodeID.h"

#include "DictBencodeNode.h"
#include "interfaces/DHTMessageSender.h"
#include "interfaces/DHTMessageHandler.h"

#include <QHostAddress>
#include <QUdpSocket>
#include <QObject>
#include <QSharedPointer>

class QDHTLIBSHARED_EXPORT QDHT : public QObject, public DHTMessageSender
{
    Q_OBJECT
public:
    QDHT();
    virtual ~QDHT();

    virtual void sendPing(const IPPort& dest,
                          quint16 transactionID,
                          const NodeID& myNodeID);

    virtual void sendPong(const IPPort& dest,
                          quint16 transactionID,
                          const NodeID& myNodeID);

    void addMessageHandler(const QSharedPointer<DHTMessageHandler>& handler);

signals:


public slots:
    void test();

private slots:
    void handleIncomingBytes();
    void beginProcessMessage(const QHostAddress& srcIP, quint16 srcPort, const QByteArray& bytes);

    void beginProcessQuery(const IPPort &src, quint16 transactionID,
                           const QByteArray& queryType,
                           const QMap<QByteArray, QSharedPointer<BencodeNode> >& queryArgs);

    void beginProcessResponse(const IPPort &src, quint16 transactionID,
                              const QMap<QByteArray, QSharedPointer<BencodeNode> >& responseArgs);

private:
    static QByteArray transactionIDToBytes(quint16 transactionID);
    static quint16 bytesToTransactionID(const QByteArray& transactionIDBytes);

    QUdpSocket * _socket;

    QList<QSharedPointer<DHTMessageHandler> > _messageHandlers;
};

#endif // QDHT_H
