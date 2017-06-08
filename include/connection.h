#ifndef CONN_TYPE_H
#define CONN_TYPE_H

#include <QHash>
#include <QString>
#include <QByteArray>
#include "store.h"
#include "typedefs.h"
#include "context.h"
#include "msg_buffer.h"
namespace Imq {

class Connection {
public:
  virtual bool send(UniqueMsgBuffer) = 0;
  virtual ~Connection() {}
};

template <typename T> class TypedConnection : Connection {
public:
  T _conn;
};
}
#endif // CONN_TYPE_H
