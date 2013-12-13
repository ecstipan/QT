#ifndef MPANEL_H
#define MPANEL_H

#include "main.h"
#include <QtCore>
#include <QtDebug>
#include <QObject>
#include "mpanelstatus.h"

class MPanel
{
public:
    explicit MPanel();
    explicit MPanel(int xpos, int ypos);
    int xPosition;
    int yPosition;
    int sideDimension;
    MPanelStatus status;
    QString uniqueID;
    QString MACAddress;
    QString IPAddress;
    unsigned short int universe;
    MPanel* leftNeighbor;
    MPanel* topNeighbor;
    MPanel* rightNeighbor;
    MPanel* bottomNeighor;

    //functions
    void setState(MPanelStatusState state);
    MPanelStatusState getState();
    long long int lastStateTime();
    bool hasFault();
    void refresh();
    MPanel* getNeighborFault();
signals:

public slots:

};

#endif // MPANEL_H
