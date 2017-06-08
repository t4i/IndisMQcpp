#ifndef MSG_BUFFER_H
#define MSG_BUFFER_H
#include <QByteArray>
#include <QHash>
#include <QString>
#include "typedefs.h"
#include "utils.h"
#include "../../IndisMQSchema/IndisMQ_generated.h"
#include "../../flatbuffers/include/flatbuffers/flatbuffers.h"

namespace schema = IndisMQ;
namespace Imq {
class MsgBuffer {
public:
  MsgBuffer() {}
  MsgBuffer(flatbuffers::unique_ptr_t _data, int size) {
    m_fbData = std::move(_data);
    fields = schema::GetImq(m_fbData.get());
    data = QByteArray::fromRawData(
        reinterpret_cast<const char *>(m_fbData.get()), size);
  }
  MsgBuffer(QByteArray _data) {
    data = _data;
    fields = schema::GetImq(data.data());
  }
  MsgBuffer(QString msgId, schema::Action action, int status, QString to,
            QString from, QString path, QString authorization = "",
            QByteArray body = QByteArray(),
            QHash<QString, QString> meta = QHash<QString, QString>(),
            Handler callback = nullptr) {

    flatbuffers::Offset<flatbuffers::String> msgIdOffset = 0, toOffset = 0,
                                             fromOffset = 0, pathOffset = 0,
                                             authorizationOffset = 0;
    flatbuffers::Offset<flatbuffers::Vector<uint8_t>> bodyOffset = 0;
    flatbuffers::Offset<
        flatbuffers::Vector<flatbuffers::Offset<schema::KeyVal>>> metaOffset =
        0;
    flatbuffers::FlatBufferBuilder builder;
    if (msgId.isEmpty()) {
      msgIdOffset = builder.CreateString(newRandId());
    } else {
      msgIdOffset = builder.CreateString(msgId.toStdString());
    }
    if (!to.isEmpty()) {
      toOffset = builder.CreateString(to.toStdString());
    }
    if (!from.isEmpty()) {
      fromOffset = builder.CreateString(from.toStdString());
    }
    if (!path.isEmpty()) {
      pathOffset = builder.CreateString(path.toStdString());
    }
    if (!authorization.isEmpty()) {
      authorizationOffset = builder.CreateString(authorization.toStdString());
    }
    if (!body.isEmpty()) {
      bodyOffset = builder.CreateVector(
          reinterpret_cast<uint8_t *>(body.data()), body.size());
    }
    if (!meta.isEmpty()) {
      std::vector<flatbuffers::Offset<schema::KeyVal>> offsets;
      QHash<QString, QString>::iterator i = meta.begin();
      while (i != meta.end()) {
        auto key = builder.CreateString(i.key().toStdString());
        auto val = builder.CreateString(i.value().toStdString());
        offsets.push_back(schema::CreateKeyVal(builder, key, val));
        ++i;
      }
      metaOffset = builder.CreateVector(offsets);
    }
    schema::ImqBuilder imqBuilder(builder);
    imqBuilder.add_MsgId(msgIdOffset);
    imqBuilder.add_Action(action);
    imqBuilder.add_Status(status);
    imqBuilder.add_To(toOffset);
    imqBuilder.add_From(fromOffset);
    imqBuilder.add_Path(pathOffset);
    imqBuilder.add_Authorization(authorizationOffset);
    imqBuilder.add_Body(bodyOffset);
    imqBuilder.add_Meta(metaOffset);
    if (callback) {
      imqBuilder.add_Callback(true);
      this->callback = callback;
    }
    auto imq = imqBuilder.Finish();
    builder.Finish(imq);
    auto size = builder.GetSize();
    m_fbData = builder.ReleaseBufferPointer();
    ;
    fields = schema::GetImq(m_fbData.get());
    data = QByteArray::fromRawData(
        reinterpret_cast<const char *>(m_fbData.get()), size);
  }

  QByteArray data;
  const schema::Imq *fields;
  Handler callback;
  qint64 timestamp;
  inline QHash<QString, QString> meta() {
    if (m_meta.empty() && fields->Meta()->Length() > 0) {
      for (uint i = 0; i < fields->Meta()->Length(); ++i) {
        m_meta.insert(
            QString::fromStdString(fields->Meta()->Get(i)->Key()->str()),
            QString::fromStdString(fields->Meta()->Get(i)->Value()->str()));
      }
    }
    return m_meta;
  }
  inline const QByteArray body() {
    if (m_body.isEmpty()) {
      if (fields->Body()->size() > 0) {
        m_body.setRawData(
            reinterpret_cast<const char *>(fields->Body()->Data()),
            fields->Body()->Length());
        // m_body=QByteArray::fromRawData(,);
      }
    }
    return m_body;
  }

  //    inline SharedMsgObject toObject(){
  //        return nullptr;
  //    }
  //    inline SharedMsgBuffer toShared(){
  //        return SharedMsgBuffer(this);
  //    }

private:
  flatbuffers::unique_ptr_t m_fbData;
  QHash<QString, QString> m_meta;
  QByteArray m_body;

  //    to convert fb vector to std vector new
  //    std::vector<uint8_t>(fields->Body()->data(),fields->Body()->data()+fields->Body()->size())
};
}
#endif
