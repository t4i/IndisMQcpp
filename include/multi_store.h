#ifndef MULTI_STORE_H
#define MULTI_STORE_H
#include <QMultiHash>
#include <QString>
#include <QReadWriteLock>

template <typename T> class MultiStore {
public:
  MultiStore() {}
  QMultiHash<QString, T> store;
  QReadWriteLock lock;
  inline QList<T> get(QString key) {
    lock.lockForRead();
    auto vals = store.values(key);
    lock.unlock();
    return vals;
  }
  inline void set(QString key, T val) {
    lock.lockForWrite();
    store.insert(key, val);
    lock.unlock();
  }
  inline int del(QString key, T val) {
    lock.lockForWrite();
    auto count = store.remove(key, val);
    lock.unlock();
    return count;
  }
  inline int del(QString key) {
    lock.lockForWrite();
    auto count = store.remove(key);
    lock.unlock();
    return count;
  }

  inline int length() {
    lock.lockForRead();
    auto length = store.size();
    lock.unlock();
    return length;
  }
};

#endif // MULTI_STORE_H
