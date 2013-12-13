#include "mpanelstatus.h"
#include "mpanel.h"
#include "main.h"

MPanel::MPanel()
{
    this->xPosition = 0;
    this->yPosition = 0;
    this->status = MPanelStatus();
    this->sideDimension = 16;
}

MPanel::MPanel(int xpos, int ypos)
{
    this->xPosition = xpos;
    this->yPosition = ypos;
    this->status = MPanelStatus();
    this->sideDimension = 16;
}

void MPanel::setState(MPanelStatusState state)
{
    this->status.setState(state);
}

MPanelStatusState MPanel::getState()
{
    return this->status.getState();
}

long long int MPanel::lastStateTime()
{
    return this->status.getTime();
}

bool MPanel::hasFault()
{
    return (this->status.getState() == DISPLAY_ERROR
            || this->status.getState() == NETWORK_ERROR
            || this->status.getState() == POWER_FAILURE
            || this->status.getState() == ADDRESS_ERROR
            || this->status.getState() == UNKNOWN_ERROR
            || this->status.getState() == TIMEOUT
           );
}

