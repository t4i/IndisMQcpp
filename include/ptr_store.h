#ifndef STORE_PTR_H
#define STORE_PTR_H
#include "store.h"
#include "memory"
namespace Imq {
template <typename T> class PtrStore : public Store<std::unique_ptr<T>> {

public:
  PtrStore() {}
  QReadWriteLock lock;
  std::unordered_map<std::string, std::unique_ptr<T>> store;
  inline std::unique_ptr<T> get(QString key) {
    lock.lockForRead();
    auto i = store.find(key.toStdString());
    lock.unlock();
    if (i != store.end()) {
      lock.lockForWrite();
      auto val = std::move(i->second);
      store.erase(i);
      lock.unlock();
      return val;
    }
    return nullptr;
  }
  inline bool has(QString key) {
    lock.lockForRead();
    auto i = store.find(key.toStdString());
    lock.unlock();
    if (i == store.end()) {
      return false;
    }
    return true;
  }

  inline T *getPtr(QString key) {
    lock.lockForRead();
    auto i = store.find(key.toStdString());
    if (i != store.end()) {
      auto val = store[key.toStdString()].get();
      lock.unlock();
      return val;
    } else {
      lock.unlock();
      return nullptr;
    }
  }

  inline void set(QString key, std::unique_ptr<T> val) {
    lock.lockForWrite();
    store[key.toStdString()] = std::move(val);
    lock.unlock();
    return;
  }
};
}

#endif // STORE_PTR_H
