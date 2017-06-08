#ifndef TYPEDEFS_H
#define TYPEDEFS_H
#include <functional>
#include <memory>
#include <QObject>
namespace Imq {

class Context;
class MsgBuffer;
class MsgObject;
// class IConnRef;
class Connection;
template <typename T> class TypedConnection;
// template <typename T> class ConnType;
// template <typename T> class ConnRef;
using UniqueMsgBuffer = std::unique_ptr<MsgBuffer>;

typedef std::unique_ptr<MsgObject> UniqueMsgObject;
// template <typename T> using UniqueConnType = std::unique_ptr<ConnType<T>>;
// template <typename T> using UniqueConnRef = std::unique_ptr<ConnRef<T>>;
// using UniqueIConnRef = std::unique_ptr<IConnRef>;
// template <typename T>
// using Sender = std::function<bool(Context *, MsgBuffer *, ConnRef<T> *)>;
// template <typename T>
// using Reciever =
//    std::function<void(Context *, UniqueMsgBuffer, UniqueConnRef<T>)>;

typedef std::function<void(Context *ctx, UniqueMsgBuffer, Connection *)>
    Handler;
enum ConnClass { NONE, HALF_DUPLEX, FULL_DUPLEX };
}
#endif // TYPEDEFS_H
