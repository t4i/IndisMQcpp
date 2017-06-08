#ifndef INDISMQ_CPP_H
#define INDISMQ_CPP_H
#include <QObject>
#include <QDebug>
#include <QByteArray>
#include <QString>
#include "connection.h"
#include "handlers.h"
#include "messages.h"
#include "subscribers.h"
#include "queues.h"
#include "connections.h"
#include "msg_buffer.h"
#include "status.h"
namespace schema = IndisMQ;
namespace Imq {

class Context : public QObject {
  Q_OBJECT
public:
  Context(QString name, bool storeMsgTime = false, QObject *parent = 0)
      : QObject(parent), name(name), messages(storeMsgTime) {}

  const QString name;
  bool debug = false;
  Handler unknownHandler;
  Handler connectionHandler;
  Handlers handlers;
  Messages messages;
  Subscribers subscribers;
  Connections connections;
  Queues queues;
};
}
#endif
