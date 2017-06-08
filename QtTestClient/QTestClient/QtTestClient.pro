QT += core websockets
QT -= gui

CONFIG += c++11

TARGET = IndisRPC
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += main.cpp \
    ../../../../IndisConnect/icPlugins/icIndisProxyPlugin/proxy_handler.cpp

HEADERS += \
    ../../include/msg_buffer.h \
    ../../include/msg_object.h \
    ../../include/multi_store.h \
    ../../include/status.h \
    ../../include/store.h \
    ../../include/typedefs.h \
    ../../include/utils.h \
    ../../include/ptr_store.h \
    ../../include/connections.h \
    ../../include/handlers.h \
    ../../include/subscribers.h \
    ../../include/connection.h \
    ../../include/conn_type.old.h \
    ../../include/conn_ref.old.h \
    ../../include/messages.h \
    ../../include/queue.h \
    ../../include/reciever.h \
    ../../include/msg_helpers.h \
    ../../include/context.h \
    ../../include/queues.h \
    ../../include/broker/broker.h \
    ../../include/broker/http.h \
    ../../include/broker/websockets.h \
    ../../../../IndisConnect/icPlugins/icIndisProxyPlugin/utils.h \
    ../../../../IndisConnect/icPlugins/icIndisProxyPlugin/networkrequest.h \
    ../../../../IndisConnect/icPlugins/icIndisProxyPlugin/bytearray.h \
    ../../../../IndisConnect/icPlugins/icIndisProxyPlugin/proxy_handler.h

DISTFILES +=
#    ../../include/connection_store.old

INCLUDEPATH += $$PWD/../../../schema
