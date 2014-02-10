
#include <QUdpSocket>
#include <QList>
#include <QNetworkInterface>
#include "mnetworksocket.h"
#include "mpanel.h"
#include "mpanelstatus.h"
#include "main.h"

MnetworkSocket::MnetworkSocket(QObject *parent) :
    QObject(parent)
{
    socket = new QUdpSocket(this);

    connect(socket, SIGNAL(readyRead()), this, SLOT(readyRead()));
}

bool MnetworkSocket::isConnected()
{
    return (this->socket->state()==QUdpSocket::BoundState);
}

bool MnetworkSocket::autoBind()
{
    QHostAddress listenAddress;
    QList<QHostAddress> list = QNetworkInterface::allAddresses();

     for(int nIter=0; nIter<list.count(); nIter++)

      {
          if(!list[nIter].isLoopback())
              if (list[nIter].protocol() == QAbstractSocket::IPv4Protocol )
                 logConsole(QString("Interface found on ").append(( list[nIter].toString())));
                 if (list[nIter].toString().contains("10.10", Qt::CaseInsensitive))
                 {
                     listenAddress = list[nIter];
                      break;
                 }

      }

    return this->socket->bind(listenAddress, 27015);
}

bool MnetworkSocket::bind(QHostAddress addr)
{
    return this->socket->bind(addr, 27015);
}

void MnetworkSocket::SendVideo(const char *addr, QByteArray data)
{
    //send the UDP packet
    if (!socket->writeDatagram(data, QHostAddress(addr), 27015))
       logConsole(QString("Cannot Sent Video Frame: UDP Disconnected"));
}

void MnetworkSocket::reAddress(const char *addr)
{
    QByteArray header(4, 255);//source address
    header.append((char)3); //control signal
    header.append((char)1); //re-address control signal
    if (!socket->writeDatagram(header, QHostAddress(addr), 27015))
       logConsole(QString("Failed Panel Readdress Process!"));
}

void MnetworkSocket::sendShutdown(const char *addr)
{
    QByteArray header(4, 255);//source address
    header.append((char)3); //control signal
    header.append((char)10); //shutdown enumeraton
    socket->writeDatagram(header, QHostAddress(addr), 27015);
}

void MnetworkSocket::close()
{
    this->socket->close();;
}

void MnetworkSocket::readyRead()
{
    QByteArray buffer;
    buffer.resize(socket->pendingDatagramSize());

    QHostAddress sender;
    quint16 senderPort;

    socket->readDatagram(buffer.data(), buffer.size(),
                             &sender, &senderPort);
    if (!sender.isLoopback())
    {
        char* data = buffer.data();
        if(buffer.size() >= 6) {
            logConsole(QString("Recieved Incoming Data Packet from ").append(sender.toString()));

            //check for addressing packet
            if(data[4] == 0x02 && data[5] == 0x03) {
                int x = (int)data[0];
                int y = (int)data[1];
                qDebug() << x << " " << y;
                if (MPanel::addPanel(x,y)) qDebug() << "Added panel!";
                MPanel::getPanelAtLocation(x,y)->setIP(sender.toString());
                logConsole(QString("New Panel Registered From ").append(sender.toString()));
            }
        }
    }
}
