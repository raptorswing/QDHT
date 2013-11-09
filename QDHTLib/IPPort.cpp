#include "IPPort.h"

#include <QDataStream>

IPPort::IPPort(const QHostAddress &host, quint16 port) :
    _host(host), _port(port)
{

}

const QHostAddress &IPPort::host() const
{
    return _host;
}

quint16 IPPort::port() const
{
    return _port;
}

QByteArray IPPort::toCompactIPPortInfo() const
{
    QByteArray toRet;

    {
        QDataStream stream(&toRet, QIODevice::WriteOnly);
        stream << this->host().toIPv4Address();
        stream << this->port();
    }

    return toRet;
}
