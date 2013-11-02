#ifndef BOOTSTRAPTEST_H
#define BOOTSTRAPTEST_H

#include <QObject>
#include <QHostAddress>
#include <QUdpSocket>
#include <QPointer>

class BootstrapTest : public QObject
{
    Q_OBJECT
public:
    explicit BootstrapTest(const QHostAddress& host, quint16 port, QObject *parent = 0);

signals:

public slots:
    void start();

private:
    void cleanup();

    QHostAddress _host;
    quint16 _port;

    QPointer<QUdpSocket> _socket;

};

#endif // BOOTSTRAPTEST_H
