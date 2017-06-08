#ifndef CONN_REF_H
#define CONN_REF_H
#include "typedefs.h"
namespace Imq {
class IConnRef {
public:
  virtual bool send(UniqueMsgBuffer) = 0;
  virtual ~IConnRef() {}
};

template <typename T> class ConnRef : public IConnRef {
public:
  ConnRef(ConnType<T> *type, T *conn) : conn(conn), type(type) {}
  T *conn;
  ConnType<T> *type;
  bool send(UniqueMsgBuffer m) {
    type->send(std::move(m), conn);
    return true;
  }
  void handleUnknown(Context *ctx, UniqueMsgBuffer m) {
    if (type->unknownHandler != nullptr) {
      type->unknownHandler(ctx, std::move(m), this);
      return;
    }
    send(makeReply(ctx, m.get(), Status::NotFound, "Not Found"));
    return;
  }
};
}
#endif // CONN_REF_H
