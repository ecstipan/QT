#ifndef MAIN_H
#define MAIN_H

#include "mpanel.h"
void logConsole(QString temp);
void openCamera();
void closeCamera();
void selectCamera(int);
void setFPS(int);
void setResolution(int);
void updateOverlay();
void sendVideoFrame(const char *addr, QByteArray data);
void startAddress(const char *addr);
void beginReaddressProcess();
void setTestPattern(int t);

void setOffsetXStart(int x);
void setOffsetXEnd(int x);
void setOffsetYStart(int x);
void setOffsetYEnd(int x);

#endif // MAIN_H

