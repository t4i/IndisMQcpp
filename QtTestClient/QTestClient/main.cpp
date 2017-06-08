#include <QCoreApplication>
#include "../../../../IndisConnect/icPlugins/icIndisProxyPlugin/proxy_handler.h"

void handler(Imq::Context *ctx, Imq::UniqueMsgBuffer m, Imq::Connection *conn) {
  qDebug() << "handler called";
  conn->send(Imq::makeReply(ctx, m.get(), Imq::Status::OK, "QT body"));
}


void processResponse(Imq::Context *ctx, Imq::UniqueMsgBuffer m, Imq::Connection *conn,QNetworkAccessManager qnam,QNetworkReply *reply){

}



void callback(Imq::Context *ctx, Imq::UniqueMsgBuffer m, Imq::Connection *) {
  qDebug() << "callback";
  qDebug() << ctx->messages.storeTime.size();
  qDebug() << ctx->messages.length();

  qDebug() << m->body();
}

// bool sender(Imq::Context *, Imq::MsgBuffer *m, Imq::Connection *conn) {
//  conn->conn->sendBinaryMessage(m->data);
//  return true;
//}

void onConnected(Imq::Context *ctx, Imq::Broker::WebSocket *conn) {
  qDebug() << "connected";
  //  std::unique_ptr<Imq::MsgBuffer> m =
  //      Imq::makeMsg(ctx, "", schema::Action::GET, 0, "srv", "/test", "",
  //                   QByteArray(), QHash<QString, QString>(), callback);
  //  m->timestamp = QDateTime::currentMSecsSinceEpoch();
  //  QString id = m->fields->MsgId()->c_str();
  //  if (!conn->send(std::move(m))) {
  //    qDebug() << "wtf";
  //  }
  //  QTimer::singleShot(1000, conn->ws, [=]() {
  //    if (ctx->messages.has(id)) {
  //      qDebug() << "timer expired";
  //      qDebug() << ctx->messages.storeTime.size();
  //      qDebug() << ctx->messages.length();
  //      qDebug() << ctx->messages.store.size();
  //      qDebug() << "delete";
  //      qDebug() << ctx->messages.delPrevMsgs(
  //          QDateTime::currentMSecsSinceEpoch());
  //      qDebug() << ctx->messages.storeTime.size();
  //      qDebug() << ctx->messages.length();
  //    }
  //  });
}
void onDisconnected() {}

int main(int argc, char *argv[]) {
  QCoreApplication a(argc, argv);
  ProxyHandler handler(&a);
  handler.createContext("client");
  handler.connectWebsocket("ws://localhost:80");
  return a.exec();
}
