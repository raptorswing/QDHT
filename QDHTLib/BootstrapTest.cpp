#include "BootstrapTest.h"

#include <QUdpSocket>

BootstrapTest::BootstrapTest(const QHostAddress &host, quint16 port, QObject *parent) :
    QObject(parent), _host(host), _port(port)
{
}

//public slot
void BootstrapTest::start()
{
    this->cleanup();

    _socket = new QUdpSocket(this);

}

//private
void BootstrapTest::cleanup()
{
    if (!_socket.isNull())
        delete _socket;
}
