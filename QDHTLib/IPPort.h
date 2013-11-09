#ifndef IPPORT_H
#define IPPORT_H

#include <QHostAddress>

class IPPort
{
public:
    IPPort(const QHostAddress& host = QHostAddress(), quint16 port = 0);

    const QHostAddress & host() const;
    quint16 port() const;

    QByteArray toCompactIPPortInfo() const;

private:
    QHostAddress _host;
    quint16 _port;
};

#endif // IPPORT_H
