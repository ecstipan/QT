#include <QtCore>
#include "mpanelstatus.h"
#include "mpanel.h"
#include "main.h"

extern MPanel *_globalPanels[122][122];

//static declarations
unsigned int MPanel::arrayWidth = 0;
unsigned int MPanel::arrayHeight = 0;
unsigned int MPanel::boundLeft = 61;
unsigned int MPanel::boundTop = 61;
unsigned int MPanel::boundRight = 61;
unsigned int MPanel::boundBottom = 61;

MPanel::MPanel()
{
    this->dataMutex = new QMutex();
    this->dataMutex->lock();
    this->xPosition = 61;
    this->yPosition = 61;
    this->status = MPanelStatus();
    this->status.setState(OFFLINE);
    this->sideDimension = 16;
    this->universe = 1;
    this->uniqueID = QString("New Panel");
    this->dataMutex->unlock();
}

MPanel::MPanel(int xpos, int ypos)
{
    this->dataMutex = new QMutex();
    this->dataMutex->lock();
    this->xPosition = xpos;
    this->yPosition = ypos;
    this->status = MPanelStatus();
    this->status.setState(OFFLINE);
    this->sideDimension = 16;
    this->universe = 1;
    this->uniqueID = QString("New Panel");
    this->dataMutex->unlock();
}

void MPanel::setState(MPanelStatusState state)
{
    this->dataMutex->lock();
    this->status.setState(state);
    this->dataMutex->unlock();
}

MPanelStatusState MPanel::getState()
{
    MPanelStatusState tempState;
    this->dataMutex->lock();
    tempState = this->status.getState();
    this->dataMutex->unlock();
    return tempState;
}

long long int MPanel::lastStateTime()
{
    long long int tempTime;
    this->dataMutex->lock();
    tempTime = this->status.getTime();
    this->dataMutex->unlock();
    return tempTime;
}

bool MPanel::hasFault()
{
    bool fault;
    this->dataMutex->lock();
    fault = (this->status.getState() == DISPLAY_ERROR
            || this->status.getState() == NETWORK_ERROR
            || this->status.getState() == POWER_FAILURE
            || this->status.getState() == ADDRESS_ERROR
            || this->status.getState() == UNKNOWN_ERROR
            || this->status.getState() == TIMEOUT
           );
    this->dataMutex->unlock();
    return fault;
}

bool MPanel::neighborHasFault(){
    if(this->xPosition > 0
            && _globalPanels[this->xPosition - 1][this->yPosition] != NULL
            && _globalPanels[this->xPosition - 1][this->yPosition]->hasFault() == true)
        return true;
    if(this->yPosition > 0
            && _globalPanels[this->xPosition][this->yPosition - 1] != NULL
            && _globalPanels[this->xPosition][this->yPosition - 1]->hasFault() == true)
        return true;
    if(this->xPosition < 121
            && _globalPanels[this->xPosition + 1][this->yPosition] != NULL
            && _globalPanels[this->xPosition + 1][this->yPosition]->hasFault() == true)
        return true;
    if(this->xPosition < 121
            && _globalPanels[this->xPosition][this->yPosition + 1] != NULL
            && _globalPanels[this->xPosition][this->yPosition + 1]->hasFault() == true)
        return true;
    //none of our neighbors are broken! yay!
    return false;
}

MPanel *MPanel::getNeighborFault(){
    if(this->xPosition > 0
            && _globalPanels[this->xPosition - 1][this->yPosition] != NULL
            && _globalPanels[this->xPosition - 1][this->yPosition]->hasFault() == true)
        return _globalPanels[this->xPosition - 1][this->yPosition];
    if(this->yPosition > 0
            && _globalPanels[this->xPosition][this->yPosition - 1] != NULL
            && _globalPanels[this->xPosition][this->yPosition - 1]->hasFault() == true)
        return _globalPanels[this->xPosition][this->yPosition - 1];
    if(this->xPosition < 121
            && _globalPanels[this->xPosition + 1][this->yPosition] != NULL
            && _globalPanels[this->xPosition + 1][this->yPosition]->hasFault() == true)
        return _globalPanels[this->xPosition + 1][this->yPosition];
    if(this->xPosition < 121
            && _globalPanels[this->xPosition][this->yPosition + 1] != NULL
            && _globalPanels[this->xPosition][this->yPosition + 1]->hasFault() == true)
        return _globalPanels[this->xPosition][this->yPosition + 1];
    //none of our neighbors are broken! yay!
    return NULL;
}

long long int MPanel::getNeighorFaultTime(){
    if(this->xPosition > 0
            && _globalPanels[this->xPosition - 1][this->yPosition] != NULL
            && _globalPanels[this->xPosition - 1][this->yPosition]->hasFault() == true)
        return _globalPanels[this->xPosition - 1][this->yPosition]->lastStateTime();
    if(this->yPosition > 0
            && _globalPanels[this->xPosition][this->yPosition - 1] != NULL
            && _globalPanels[this->xPosition][this->yPosition - 1]->hasFault() == true)
        return _globalPanels[this->xPosition][this->yPosition - 1]->lastStateTime();
    if(this->xPosition < 121
            && _globalPanels[this->xPosition + 1][this->yPosition] != NULL
            && _globalPanels[this->xPosition + 1][this->yPosition]->hasFault() == true)
        return _globalPanels[this->xPosition + 1][this->yPosition]->lastStateTime();
    if(this->xPosition < 121
            && _globalPanels[this->xPosition][this->yPosition + 1] != NULL
            && _globalPanels[this->xPosition][this->yPosition + 1]->hasFault() == true)
        return _globalPanels[this->xPosition][this->yPosition + 1]->lastStateTime();
    //none of our neighbors are broken! yay!
    return -1;
}

void MPanel::refresh()
{
    this->dataMutex->lock();
    //do things to repull neighbors and whatnot... that's it so far

    this->dataMutex->unlock();
}

bool MPanel::setPosition(int xpos, int ypos)
{
    if (xpos < 0 || xpos > 121 || ypos < 0 || ypos > 121 )
        return false;
    if (_globalPanels[xpos][ypos] != NULL) {
        return false;
    }
    _globalPanels[this->xPosition][this->yPosition] = NULL;
    this->dataMutex->lock();
    this->xPosition = xpos;
    this->yPosition = ypos;
    this->dataMutex->unlock();
    _globalPanels[xpos][ypos] = this;

    if (_globalPanels[xpos][ypos] != this) return false;
    return true;
}

int MPanel::getXPosition()
{
    int tempPos;
    this->dataMutex->lock();
    tempPos = this->xPosition;
    this->dataMutex->unlock();
    return tempPos;
}

int MPanel::getYPosition()
{
    int tempPos;
    this->dataMutex->lock();
    tempPos = this->yPosition;
    this->dataMutex->unlock();
    return tempPos;
}

void MPanel::setDimension(int dim)
{
    if (dim > 0) {
        this->dataMutex->lock();
        this->sideDimension = dim;
        this->dataMutex->unlock();
    }
}

int MPanel::getDimension()
{
    int tempDim;
    this->dataMutex->lock();
    tempDim = this->sideDimension;
    this->dataMutex->unlock();
    return tempDim;
}

void MPanel::setIP(QString ip)
{
    this->dataMutex->lock();
    this->IPAddress = QString(ip);
    this->dataMutex->unlock();
}

QString MPanel::getIP()
{
    QString tempString;
    this->dataMutex->lock();
    if (this->status.getState()==OFFLINE)
        tempString = QString("127.0.0.1");
    else
        tempString = this->IPAddress;
    this->dataMutex->unlock();
    return tempString;
}

void MPanel::setMAC(QString mac)
{
    this->dataMutex->lock();
    this->MACAddress = QString(mac);
    this->dataMutex->unlock();
}

QString MPanel::getMAC()
{
    QString tempString;
    this->dataMutex->lock();
    if (this->status.getState()==OFFLINE)
        tempString = QString("UNKNOWN");
    else
        tempString = this->MACAddress;
    this->dataMutex->unlock();
    return tempString;
}

void MPanel::setID(QString id)
{
    this->dataMutex->lock();
    this->uniqueID = QString(id);
    this->dataMutex->unlock();
}

QString MPanel::getID()
{
    QString tempString;
    this->dataMutex->lock();
    tempString = this->uniqueID;
    this->dataMutex->unlock();
    return tempString;
}

void MPanel::setUniverse(int universe)
{
    if (universe > 0) {
        this->dataMutex->lock();
        this->universe = universe;
        this->dataMutex->unlock();
    }
}

unsigned short int MPanel::getUniverse()
{
    unsigned short int tempUniverse;
    this->dataMutex->lock();
    tempUniverse = this->universe;
    this->dataMutex->unlock();
    return tempUniverse;
}

/*=========================
 *Static Methods
 *=======================*/

bool MPanel::addPanel(int xpos, int ypos)
{
    if (xpos < 0 || xpos > 121 || ypos < 0 || ypos > 121 )
        return false;
    if (_globalPanels[xpos][ypos] == NULL) {
        _globalPanels[xpos][ypos] = new MPanel();
        if (_globalPanels[xpos][ypos] == NULL)
            return false;
        //do a final idiot check
        if (_globalPanels[xpos][ypos]->getState() == OFFLINE)
            return true;
    }
    return false;
}

bool MPanel::deletePanel(int xpos, int ypos)
{
    if (xpos < 0 || xpos > 121 || ypos < 0 || ypos > 121 )
        return false;
    if (_globalPanels[xpos][ypos] != NULL) {
        _globalPanels[xpos][ypos]->~MPanel();
        _globalPanels[xpos][ypos] = NULL;
        if (_globalPanels[xpos][ypos] != NULL)
            return false;
    }
    return true;
}

bool MPanel::panelExistsAt(int xpos, int ypos)
{
    if (xpos < 0 || xpos > 121 || ypos < 0 || ypos > 121 )
        return false;
    if (_globalPanels[xpos][ypos] != NULL) {
        return true;
    }
    return false;
}

MPanel* MPanel::getPanelAtLocation(int xpos, int ypos)
{
    if (xpos < 0 || xpos > 121 || ypos < 0 || ypos > 121 )
        return NULL;
    if (_globalPanels[xpos][ypos] != NULL) {
        return _globalPanels[xpos][ypos];
    }
    return NULL;
}

unsigned int MPanel::getArrayWidth()
{
    int width = getArrayBoundRight() - getArrayBoundLeft() + 1;
    return (width > 0) ? width : 0;
}

unsigned int MPanel::getArrayHeight()
{
    int height = getArrayBoundBottom() - getArrayBoundTop() + 1;
    return (height > 0) ? height : 0;
}

unsigned int MPanel::getArrayBoundLeft()
{
    unsigned int lBound = 0;
    int curx, cury;
    for(curx = 0; curx < 121; curx++){
        for(cury = 0; cury < 121; cury++){
            lBound = curx;
            if(MPanel::panelExistsAt(curx, cury)) return lBound;
        }
    }
    return 121;
}

unsigned int MPanel::getArrayBoundTop()
{
    unsigned int tBound = 0;
    int curx, cury;
    for(cury = 0; cury < 121; cury++){
        for(curx = 0; curx < 121; curx++){
            tBound = cury;
            if(MPanel::panelExistsAt(curx, cury)) return tBound;
        }
    }
    return 121;
}

unsigned int MPanel::getArrayBoundRight()
{
    unsigned int rBound = 121;
    int curx, cury;
    for(curx = 121; curx > 0; curx--){
        for(cury = 0; cury < 121; cury++){
            rBound = curx;
            if(MPanel::panelExistsAt(curx, cury)) return rBound;
        }
    }
    return 0;
}

unsigned int MPanel::getArrayBoundBottom()
{
    unsigned int bBound = 0;
    int curx, cury;
    for(cury = 121; cury > 0; cury--){
        for(curx = 121; curx > 0; curx--){
            bBound = cury;
            if(MPanel::panelExistsAt(curx, cury)) return bBound;
        }
    }
    return 0;
}

void MPanel::refreshLocalArrayMap()
{
    MPanel::arrayWidth = MPanel::getArrayWidth();
    MPanel::arrayHeight = MPanel::getArrayHeight();
    MPanel::boundLeft = MPanel::getArrayBoundLeft();
    MPanel::boundTop = MPanel::getArrayBoundTop();
    MPanel::boundRight = MPanel::getArrayBoundRight();
    MPanel::boundBottom = MPanel::getArrayBoundBottom();

    //do other things as necessary
}

unsigned int MPanel::getArrayCount()
{
    unsigned int panelCount = 0;
    unsigned int blockx, blocky;
    //sweep thorugh each block
    for (blockx = 0; blockx < MPanel::arrayWidth; blockx++)
    {
        for (blocky = 0; blocky < MPanel::arrayHeight; blocky++)
        {
            //Add a block if there's a panel
            if (MPanel::panelExistsAt(MPanel::boundLeft + blockx,
                                      MPanel::boundTop + blocky))
                panelCount++;
        }
    }
    return panelCount;
}

MPanel::~MPanel()
{

    this->dataMutex->lock();
    this->dataMutex->~QMutex();
}
