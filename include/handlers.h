#ifndef HANDLER_STORE_H
#define HANDLER_STORE_H
#include "typedefs.h"
#include "store.h"
namespace Imq {
class Handlers : public Store<Handler> {
public:
  Handlers() {}
};
}
#endif
