#ifndef MNETWORKSOCKET_H
#define MNETWORKSOCKET_H

#include <QObject>
#include <QUdpSocket>

class MnetworkSocket : public QObject
{
    Q_OBJECT

public:
    explicit MnetworkSocket(QObject *parent = 0);
    void SendVideo(const char *addr, QByteArray data);
    void reAddress(const char *addr);
    bool isConnected();
    bool autoBind();
    bool bind(QHostAddress addr);
    void sendShutdown(const char *addr);
    void close();

signals:

public slots:
    void readyRead();

private:
    QUdpSocket *socket;

};

#endif // MNETWORKSOCKET_H
