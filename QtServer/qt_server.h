#ifndef QTSERVER_H
#define QTSERVER_H

#include <QObject>
#include "../indis_rpc.h"
class QtServer : public QObject
{
    Q_OBJECT
public:
    explicit QtServer(QObject *parent = 0);

signals:

public slots:
};

#endif // QTSERVER_H
