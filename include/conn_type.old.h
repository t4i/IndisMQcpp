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
template <typename T> class ConnType {
  Imq *ctx;

public:
  ConnType() {}
  ConnType(Imq *ctx, Sender<T> sender, ConnClass connClass,
           Handler unknownHandler = nullptr,
           Reciever<T> reciever = defaultReciever)
      : ctx(ctx), sender(sender), connClass(connClass), reciever(reciever),
        unknownHandler(unknownHandler) {}
  Sender<T> sender;
  Reciever<T> reciever;
  Handler unknownHandler;
  ConnClass connClass;
  bool send(UniqueMsgBuffer m, T *conn) {
    auto success = sender(ctx, m.get(), this->ref(conn).get());
    if (success && m->callback) {
      QString from = m->fields->MsgId()->c_str();
      ctx->msgStore.set(from, std::move(m));
    }
    return success;
  }

  void recieve(UniqueMsgBuffer m, T *conn) {
    return reciever(context, std::move(m), conn);
  }
  void recieve(QByteArray data, T *conn) {
    if (data.isEmpty()) {
      return;
    }
    auto m = UniqueMsgBuffer(new MsgBuffer(data));
    reciever(ctx, std::move(m), this->ref(conn));
  }
  UniqueConnRef<T> ref(T *conn) {
    return UniqueConnRef<T>(new ConnRef<T>(this, conn));
  }

  inline static void defaultReciever(Imq *ctx, UniqueMsgBuffer m,
                                     UniqueConnRef<T> connRef) {
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
      connRef->handleUnknown(ctx, std::move(m));
      return;
    }
    switch (m->fields->Action()) {
    case schema::Action::RESPONSE: {

      UniqueMsgBuffer om = ctx->msgStore.get(msgId);
      if (om != nullptr) {
        om->callback(ctx, std::move(m), connRef.get());
        return;
      }
    } break;
    case schema::Action::SUBSCRIBE: {
      auto subConn = ctx->connectionStore.get(from);
      if (subConn == nullptr) {
        if (connRef->type->connClass >= ConnClass::FULL_DUPLEX) {
          auto c = connRef.get();
          ctx->connectionStore.set(from, std::move(connRef));
          ctx->subscriberStore.set(from, m->fields->Path()->c_str());
          c->send(makeReply(ctx, m.get(), Status::OK));
          return;
        } else {
          connRef->send(makeReply(ctx, m.get(), Status::BadGateway));
          return;
        }
      }

    } break;
    case schema::Action::UNSUBSCRIBE: {
      ctx->subscriberStore.del(from, m->fields->Path()->c_str());
      connRef->send(makeReply(ctx, m.get(), Status::OK));
      return;
    } break;
    case schema::Action::CONNECT: {
      if (connRef->type->connClass >= ConnClass::FULL_DUPLEX) {
        auto c = connRef.get();
        ctx->connectionStore.set(from, std::move(connRef));
        c->send(makeReply(ctx, m.get(), Status::OK));
        return;
      } else {
        UniqueMsgBuffer r = makeReply(ctx, m.get(), Status::BadGateway);
        connRef->send(std::move(m));
        return;
      }
    } break;
    case schema::Action::PUBLISH: {
      QString path = m->fields->Path()->c_str();
      Handler handler = ctx->handlerStore.get(path);
      if (handler) {
        handler(ctx, std::move(m), connRef.get());
        return;
      }
      QStringList subs = ctx->subscriberStore.get(path);
      for (int i = 0; i < subs.size(); ++i) {
        IConnRef *subConn(ctx->connectionStore.getPtr(subs.at(i)));
        if (subConn) {
          subConn->send(std::move(m));
          return;
        }
      }
    } break;

    default: {
      QString path = m->fields->Path()->c_str();
      Handler handler = ctx->handlerStore.get(path);
      if (handler) {
        handler(ctx, std::move(m), connRef.get());
        return;
      } else {
        connRef->send(makeReply(ctx, m.get(), Status::NotFound, "Not Found"));
        return;
      }
    } break;
    }
    if (m->fields->Callback()) {
      // made it this far has call back so send something
      connRef->send(makeReply(ctx, m.get(), Status::OK));
    }
  }
};
}

#endif // CONN_TYPE_H
