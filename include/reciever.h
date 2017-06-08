#ifndef RECIEVER_H
#define RECIEVER_H

#include <QString>
#include "typedefs.h"
#include "msg_buffer.h"
#include "msg_helpers.h"
#include "context.h"
namespace Imq {

inline static void recieve(Context *ctx, UniqueMsgBuffer m, Connection *conn) {
  QString msgId(m->fields->MsgId()->c_str());
  QString from(m->fields->From()->c_str());
  QString to = "";
  if (m->fields->To()) {
    to = (m->fields->To()->c_str());
  }
  if (m == nullptr) {
    return;
  }
  if (!to.isEmpty() && to != ctx->name) {
    // connRef->handleUnknown(ctx, std::move(m));
    return;
  }
  switch (m->fields->Action()) {
  case schema::Action::RESPONSE: {

    UniqueMsgBuffer om = ctx->messages.get(msgId);
    if (om != nullptr) {
      om->callback(ctx, std::move(m), conn);
      return;
    }
  } break;
  case schema::Action::SUBSCRIBE: {
    auto subConn = ctx->connections.get(from);
    if (subConn == nullptr) {
      //      if (connRef->type->connClass >= ConnClass::FULL_DUPLEX) {
      //        auto c = connRef.get();
      //        ctx->connections.set(from, std::move(connRef));
      //        ctx->subscribers.set(from, m->fields->Path()->c_str());
      //        c->send(makeReply(ctx, m.get(), Status::OK));
      //        return;
      //      } else {
      //        connRef->send(makeReply(ctx, m.get(), Status::BadGateway));
      //        return;
      //      }
    }

  } break;
  case schema::Action::UNSUBSCRIBE: {
    ctx->subscribers.del(from, m->fields->Path()->c_str());
    conn->send(makeReply(ctx, m.get(), Status::OK));
    return;
  } break;
  case schema::Action::CONNECT: {
    //    if (connRef->type->connClass >= ConnClass::FULL_DUPLEX) {
    //      auto c = connRef.get();
    //      ctx->connections.set(from, std::move(connRef));
    //      c->send(makeReply(ctx, m.get(), Status::OK));
    //      return;
    //    } else {
    //      UniqueMsgBuffer r = makeReply(ctx, m.get(), Status::BadGateway);
    //      connRef->send(std::move(m));
    //      return;
    //    }
  } break;
  case schema::Action::CAST: {
    QString path = m->fields->Path()->c_str();
    Handler handler = ctx->handlers.get(path);
    if (handler) {
      handler(ctx, std::move(m), conn);
      return;
    }
    QStringList subs = ctx->subscribers.get(path);
    for (int i = 0; i < subs.size(); ++i) {
      Connection *subConn(ctx->connections.getPtr(subs.at(i)));
      if (subConn) {
        subConn->send(std::move(m));
        return;
      }
    }
  } break;

  default: {
    QString path = m->fields->Path()->c_str();
    Handler handler = ctx->handlers.get(path);
    if (handler) {
      handler(ctx, std::move(m), conn);
      return;
    } else {
      conn->send(makeReply(ctx, m.get(), Status::NotFound, "Not Found"));
      return;
    }
  } break;
  }
  if (m->fields->Callback()) {
    // made it this far has call back so send something
    conn->send(makeReply(ctx, m.get(), Status::OK));
  }
}
inline static void recieveRaw(Context *ctx, QByteArray data, Connection *conn) {
  recieve(ctx, UniqueMsgBuffer(new MsgBuffer(data)), conn);
}
}
#endif // RECIEVER_H
