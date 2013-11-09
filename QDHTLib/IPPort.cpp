#include "IPPort.h"

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
