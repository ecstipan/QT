#ifndef MPANEL_H
#define MPANEL_H

#include <QtCore>
#include <QtDebug>
#include <QObject>

class MPanel : public QObject
{
    Q_OBJECT
public:
    explicit MPanel(QObject *parent = 0);

signals:

public slots:

};

#endif // MPANEL_H
