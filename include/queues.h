#ifndef QUEUES_H
#define QUEUES_H
#include <QMultiMap>
#include "queue.h"
#include "ptr_store.h"
#include <QReadWriteLock>
namespace Imq {
class Queues : public PtrStore<Queue> {
public:
  Queues() {}
  //  bool useStoreTime;
  //  QMultiMap<qint64, MsgBuffer *> storeTime;
  //  QReadWriteLock storeTimeLock;
  //  inline bool storeMsg(UniqueMsgBuffer m) {
  //    if (m->callback != nullptr) {
  //      QString id = m->fields->MsgId()->c_str();
  //      set(id, std::move(m));
  //      return true;
  //    }
  //    return false;
  //  }
  //  inline UniqueMsgBuffer get(QString key) {
  //    auto msg = PtrStore::get(key);
  //    if (msg != nullptr) {
  //      if (msg->timestamp > 0 && useStoreTime) {
  //        storeTimeLock.lockForWrite();
  //        storeTime.remove(msg->timestamp, msg.get());
  //        storeTimeLock.unlock();
  //      }
  //    }
  //    return msg;
  //  }

  //  inline void set(QString key, UniqueMsgBuffer val) {
  //    if (useStoreTime && val->timestamp > 0) {

  //      storeTimeLock.lockForWrite();
  //      storeTime.insert(val->timestamp, val.get());
  //      storeTimeLock.unlock();
  //    }
  //    PtrStore::set(key, std::move(val));
  //    return;
  //  }
  //  inline size_t del(QString key) {
  //    auto i = store.find(key.toStdString());
  //    if (i != store.end()) {
  //      if (i->second->timestamp > 0 && useStoreTime) {
  //        storeTimeLock.lockForWrite();
  //        storeTime.remove(i->second->timestamp, i->second.get());
  //        storeTimeLock.unlock();
  //      }
  //      return PtrStore::del(key);
  //    }
  //    return 0;
  //  }

  //  inline QList<MsgBuffer *> getPrevMsgPtrs(qint64 timestamp) {
  //    QList<MsgBuffer *> msgs;
  //    storeTimeLock.lockForRead();
  //    QMultiMap<qint64, MsgBuffer *>::iterator i = storeTime.begin();
  //    while (i != storeTime.end() && i.key() <= timestamp) {
  //      if (auto t = i.value()) {

  //        if (const char *id = i.value()->fields->MsgId()->c_str()) {
  //          msgs.append(getPtr(id));
  //        }
  //      }
  //    }
  //    storeTimeLock.unlock();
  //    return msgs;
  //  }
  //  inline int delPrevMsgs(qint64 timestamp) {
  //    int count = 0;
  //    storeTimeLock.lockForWrite();
  //    QMultiMap<qint64, MsgBuffer *>::iterator i = storeTime.begin();
  //    while (i != storeTime.end() && i.key() <= timestamp) {
  //      if (const char *id = i.value()->fields->MsgId()->c_str()) {
  //        store.erase(id);
  //      }
  //      storeTime.erase(i);
  //      count++;
  //    }
  //    storeTimeLock.unlock();
  //    return count;
  //  }
};
}
#endif
