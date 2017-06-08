#ifndef STORE_H
#define STORE_H
#include "unordered_map"
#include <QString>
#include <QReadWriteLock>

template <typename T> class Store {
public:
  Store() {}
  QReadWriteLock lock;
  std::unordered_map<std::string, T> store;
  inline T get(QString key) {
    lock.lockForRead();
    auto i = store.find(key.toStdString());
    if (i != store.end()) {
      auto val = i->second;
      lock.unlock();
      return val;
    } else {
      lock.unlock();
      return nullptr;
    }
  }
  inline void set(QString key, T val) {
    lock.lockForWrite();
    store[key.toStdString()] = val;
    lock.unlock();
  }
  inline size_t del(QString key) {
    lock.lockForWrite();
    auto count = store.erase(key.toStdString());
    lock.unlock();
    return count;
  }
  inline size_t length() {
    lock.lockForRead();
    auto length = store.size();
    lock.unlock();
    return length;
  }
};

#endif // STORE_H
