#ifndef MPANEL_H
#define MPANEL_H

#include "main.h"
#include <QtCore>
#include <QtDebug>
#include <QObject>
#include "mpanelstatus.h"
#include "QMutex.h"

class MPanel
{
public:
    explicit MPanel();
    explicit MPanel(int xpos, int ypos);
    ~MPanel();

    QMutex *dataMutex;
    int xPosition;
    int yPosition;
    int sideDimension;
    MPanelStatus status;
    QString uniqueID;
    QString MACAddress;
    QString IPAddress;
    unsigned short int universe;

    //functions
    void setState(MPanelStatusState state);
    MPanelStatusState getState();
    long long int lastStateTime();
    bool hasFault();
    bool neighborHasFault();
    void refresh();
    MPanel* getNeighborFault();
    long long int getNeighorFaultTime();

    //add the bunches of setters and getters
    bool setPosition(int xpos, int ypos);
    int getXPosition();
    int getYPosition();
    void setDimension(int dim);
    int getDimension();
    void setIP(QString ip);
    QString getIP();
    void setMAC(QString mac);
    QString getMAC();
    void setID(QString id);
    QString getID();
    void setUniverse(int universe);
    unsigned short int getUniverse();

    //Static functions for adding new panels to our array
    static bool addPanel(int xpos, int ypos);
    static bool deletePanel(int xpos, int ypos);
    static bool panelExistsAt(int xpos, int ypos);
    static MPanel* getPanelAtLocation(int xpos, int ypos);
signals:

public slots:

};

#endif // MPANEL_H
