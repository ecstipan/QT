
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

    QHostAddress listenAddress;
    QList<QHostAddress> list = QNetworkInterface::allAddresses();

     for(int nIter=0; nIter<list.count(); nIter++)

      {
          if(!list[nIter].isLoopback())
              if (list[nIter].protocol() == QAbstractSocket::IPv4Protocol )
                 logConsole(QString("Interface found on ").append(( list[nIter].toString())));

                 if (list[nIter].toString().contains("130.215", Qt::CaseInsensitive))
                 {
                     listenAddress = list[nIter];
                     logConsole(QString("Listening on ").append(( list[nIter].toString())));
                 }

      }

    if (socket->bind(listenAddress, 27015))
        logConsole(QString("UDP Connected!"));
    else
        logConsole(QString("UDP Failed to Connect!"));

    connect(socket, SIGNAL(readyRead()), this, SLOT(readyRead()));
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
    header.append((char)3); //For Video frame data
    header.append((char)1); //This is the first 16x16 chunk
    if (socket->writeDatagram(header, QHostAddress(addr), 27015))
       logConsole(QString("Starting Panel Readdress Process..."));
}

void MnetworkSocket::readyRead()
{
    QByteArray buffer;
    buffer.resize(socket->pendingDatagramSize());

    QHostAddress sender;
    quint16 senderPort;

    socket->readDatagram(buffer.data(), buffer.size(),
                             &sender, &senderPort);
    char* data = buffer.data();
    if(buffer.size() >= 6) {
        logConsole(QString("Recieved Incoming Data Packet"));

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
