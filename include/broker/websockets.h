#ifndef WEBSOCKETS_H
#define WEBSOCKETS_H

#include "../connection.h"
#include <QtWebSockets>
namespace Imq {
namespace Broker {
class WebSocket : public Connection {
public:
  WebSocket(QObject *parent = 0) {
    ws = new QWebSocket("", QWebSocketProtocol::VersionLatest, parent);
  }
  ~WebSocket() {}
  QWebSocket *ws;
  // Connection interface
public:
  inline bool send(UniqueMsgBuffer m) {
    ws->sendBinaryMessage(m->data);
    return true;
  }
};
}
}

#endif
