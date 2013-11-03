#ifndef QDHT_H
#define QDHT_H

#include "qdhtlib_global.h"

#include "NodeID.h"

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

private:
    static QByteArray transactionIDToBytes(quint16 transactionID);
    QUdpSocket * _socket;
};

#endif // QDHT_H
