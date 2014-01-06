#include <QtCore>
#include "mpanelstatus.h"
#include "mpanel.h"
#include "main.h"

extern MPanel *_globalPanels[121][121];

//static declarations
unsigned short int MPanel::arrayWidth = 0;
unsigned short int MPanel::arrayHeight = 0;
unsigned short int MPanel::boundLeft = 61;
unsigned short int MPanel::boundTop = 61;
unsigned short int MPanel::boundRight = 61;
unsigned short int MPanel::boundBottom = 61;

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

unsigned short int MPanel::getArrayWidth()
{
    return getArrayBoundRight() - getArrayBoundLeft() + 1;
}

unsigned short int MPanel::getArrayHeight()
{
    return getArrayBoundBottom() - getArrayBoundTop() + 1;
}

unsigned short int MPanel::getArrayBoundLeft()
{
    return 0;
}

unsigned short int MPanel::getArrayBoundTop()
{
    return 0;
}

unsigned short int MPanel::getArrayBoundRight()
{
    return 0;
}

unsigned short int MPanel::getArrayBoundBottom()
{
    return  0;
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

MPanel::~MPanel()
{

    this->dataMutex->lock();
    this->dataMutex->~QMutex();
}
