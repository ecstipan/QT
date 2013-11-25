#ifndef MPANELSTATUS_H
#define MPANELSTATUS_H

#include <QtCore>
#include <QtDebug>
#include <QObject>

enum MPanelStatusState { IDLE,
                         ROOT,
                         ADDRESSING,
                       };

class MPanelStatus : public QObject
{
    Q_OBJECT
public:
    explicit MPanelStatus(QObject *parent = 0);

signals:

public slots:

};

#endif // MPANELSTATUS_H
