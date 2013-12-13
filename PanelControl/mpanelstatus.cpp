#include "mpanelstatus.h"
#include <time.h>

MPanelStatus::MPanelStatus()
{
    this->statusState = OFFLINE;
    time_t times;
    time(&times);
    this->timeDetected = (int) times;
}

MPanelStatusState MPanelStatus::getState()
{
    return this->statusState;
}

void MPanelStatus::setState(MPanelStatusState state)
{
    this->statusState = state;
    time_t times;
    time(&times);
    this->timeDetected = (int) times;
}

long long int MPanelStatus::getTime()
{
    return this->timeDetected;
}
