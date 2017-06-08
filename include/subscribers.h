#ifndef SUBSCRIBER_STORE_H
#define SUBSCRIBER_STORE_H
//#include "msg_buffer.h"
#include "multi_store.h"
#include <QString>
namespace Imq {
class Subscribers : public MultiStore<QString> {
public:
  Subscribers() {}
};
}
#endif
