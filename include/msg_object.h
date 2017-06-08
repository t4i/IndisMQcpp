#ifndef MSG_OBJECT_H
#define MSG_OBJECT_H
#include "msg_buffer.h"
#include "typedefs.h"
//#include "handler_store.h"
namespace Imq {
class MsgObject {
  MsgObject() {}
  MsgObject(QString to, int action, QString path, QByteArray body,
            Handler callback)
      : to(to), action(action), path(path), body(body), callback(callback) {}
  MsgObject(MsgBuffer m)
      : msgId(m.fields->MsgId()), action(m.fields->Action()),
        to(m.fields->To()), from(m.fields->From()), path(m.fields->Path()),
        authorization(m.fields->Authorization()), body(m.fields->Body()),
        meta(m.meta()), callback(m.callback)

  {}
  QString msgId;
  int action;
  int status;
  QString to;
  QString from;
  QString path;
  QString authorization;
  QByteArray body;
  QHash<QString, QString> meta;
  Handler callback;

  inline SharedMsgBuffer toBuffer() {}
};
}
#endif
