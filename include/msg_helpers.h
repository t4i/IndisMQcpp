#ifndef HELPERS_H
#define HELPERS_H

#include "context.h"

namespace Imq {

inline UniqueMsgBuffer makeReply(Context *ctx, MsgBuffer *m, int status,
                                 QByteArray body = QByteArray()) {
  if (m->fields->Callback()) {
    return UniqueMsgBuffer(new MsgBuffer(
        m->fields->MsgId()->c_str(), schema::Action::RESPONSE, status,
        m->fields->From()->c_str(), ctx->name, "", "", body));
  }
  return nullptr;
}

inline UniqueMsgBuffer NewConnectionMsg(Context *ctx, QString to,
                                        QString authorization,
                                        Handler callback) {
  return UniqueMsgBuffer(new MsgBuffer(NULL, schema::Action::CONNECT, NULL, to,
                                       ctx->name, "", authorization, NULL,
                                       QHash<QString, QString>(), callback));
}

inline UniqueMsgBuffer
makeMsg(Context *ctx, QString msgId, schema::Action action, int status,
        QString to, QString path, QString authorization = "",
        QByteArray body = QByteArray(),
        QHash<QString, QString> meta = QHash<QString, QString>(),
        Handler callback = nullptr) {
  return UniqueMsgBuffer(new MsgBuffer(msgId, action, status, to, ctx->name,
                                       path, authorization, body, meta,
                                       callback));
}
}

#endif // HELPERS_H
