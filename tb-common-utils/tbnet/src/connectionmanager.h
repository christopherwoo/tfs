/*
 * (C) 2007-2010 Taobao Inc.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 *
 *
 * Version: $Id$
 *
 * Authors:
 *   duolong <duolong@taobao.com>
 *
 */

#ifndef TBNET_CONNECTION_MANAGER_H_
#define TBNET_CONNECTION_MANAGER_H_

#include <ext/hash_map>
//using namespace __gnu_cxx;

namespace tbnet {

typedef __gnu_cxx::hash_map<uint64_t, Connection*, __gnu_cxx::hash<int> > TBNET_CONN_MAP;

class ConnectionManager {
public:
    /*
     * ���캯��
     */
    ConnectionManager(Transport *transport, IPacketStreamer *streamer, IPacketHandler *packetHandler);

    /*
     * ��������
     */
    ~ConnectionManager();


    /**
     * ������
     */
    Connection *connect(uint64_t serverId, IPacketHandler *packetHandler, int queueLimit, int queueTimeout);

    /**
     * �ر�����
     */
    void disconnect(uint64_t serverId);

    /**
     * ���� _queueLimit
     */
    void setDefaultQueueLimit(uint64_t serverId, int queueLimit);

    /**
     * ���� _queueTimeout
     */
    void setDefaultQueueTimeout(uint64_t serverId, int queueTimeout);

    /**
     * ����packetHandler
     */
    void setDefaultPacketHandler(uint64_t serverId, IPacketHandler *packetHandler);

    /**
     * �������ݰ�
     */
    bool sendPacket(uint64_t serverId, Packet *packet, IPacketHandler *packetHandler = NULL, void *args = NULL, bool noblocking = true);

    /**
     * destroy
     */
    void cleanup();

    /**
     * �õ�һ����
     */
    Connection *getConnection(uint64_t serverId);

    /**
     * �Ƿ��ܱ�����
     */
    static bool isAlive(uint64_t serverId);

private:
    Transport *_transport;
    IPacketStreamer *_streamer;
    IPacketHandler *_packetHandler;
    int _queueLimit;
    int _queueTimeout;
    int _status;

    TBNET_CONN_MAP _connectMap;
    tbsys::CThreadMutex _mutex;
};

}

#endif

