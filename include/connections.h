#ifndef CONNECTION_STORE_H
#define CONNECTION_STORE_H
#include <QIODevice>
//#include "msg_buffer.h"
//#include "conn_type.h"
#include "ptr_store.h"
#include "typedefs.h"
namespace Imq {
class Connections : public PtrStore<Connection> {
public:
  Connections() {}
};
}
#endif
