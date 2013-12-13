#ifndef MPANELSTATUS_H
#define MPANELSTATUS_H

#include <QtCore>
#include <QtDebug>
#include <QObject>
#include <time.h>

enum MPanelStatusState { OFFLINE,
                         IDLE,
                         ROOT,
                         ADDRESSING,
                         DISPLAY_ERROR,
                         NETWORK_ERROR,
                         POWER_FAILURE,
                         ADDRESS_ERROR,
                         UNKNOWN_ERROR,
                         TIMEOUT,
                         NEIGHBOR_FAULT_L,
                         NEIGHBOR_FAULT_U,
                         NEIGHBOR_FAULT_R,
                         NEIGHBOR_FAULT_D
                       };

class MPanelStatus
{
public:
    explicit MPanelStatus();
    long long int timeDetected;
    MPanelStatusState statusState;
    MPanelStatusState getState();
    void setState(MPanelStatusState);
    long long int getTime();
signals:

public slots:

};

#endif // MPANELSTATUS_H
