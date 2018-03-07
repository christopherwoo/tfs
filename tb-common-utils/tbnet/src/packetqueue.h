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

#ifndef TBNET_PACKET_QUEUE_H_
#define TBNET_PACKET_QUEUE_H_

namespace tbnet {

class PacketQueue {
    friend class PacketQueueThread;
public:
    /*
     * ���캯��
     */
    PacketQueue();

    /*
     * ��������
     */
    ~PacketQueue();

    /*
     * ����
     */
    Packet *pop();

    /*
     * ���
     */
    void clear();

    /*
     * ����
     */
    void push(Packet *packet);

    /*
     * ����
     */
    int size();

    /*
     * �Ƿ�Ϊ��
     */
    bool empty();

    /*
     * �ƶ�������������
     */
    void moveTo(PacketQueue *destQueue);

    /*
     * �õ���ʱ��packet
     */
    Packet *getTimeoutList(int64_t now);

    /*
     * ȡ��packet list
     */
    Packet *getPacketList();

    /*
     *ȡ�ö���ͷָ��
     */
    Packet *head()
    {
        return _head;
    }
    /*
     *ȡ�ö���βָ��
     */
    Packet* tail()
    {
        return _tail;
    }
protected:
    Packet *_head;  // ��ͷ
    Packet *_tail;  // ��β
    int _size;      // Ԫ������
};

}

#endif

