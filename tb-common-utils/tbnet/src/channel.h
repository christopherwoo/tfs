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

#ifndef TBNET_CHANNEL_H_
#define TBNET_CHANNEL_H_

namespace tbnet {

class Channel {
    friend class ChannelPool;

public:
    /*
     * ���캯��
     */
    Channel();

    /*
     * ����
     *
     * @param   chid    ChannelID
     */
    void setId(uint32_t id);

    /*
     * �õ�Channel ID
     */
    uint32_t getId();

    /*
     * ���ûش�����
     */
    void setArgs(void *args);

    /*
     * ȡ���ش�����
     */
    void *getArgs();

    /*
     * ����packethandler�ľ��
     */
    void setHandler(IPacketHandler *handler);

    /*
     * �õ����
     */
    IPacketHandler *getHandler();

    /*
     * ���ù���ʱ��, ����ʱ��
     *
     * @param   expireTime
     */
    void setExpireTime(int64_t expireTime);

    /* ����ʱ�� */
    int64_t getExpireTime() {
        return _expireTime;
    }

    /*
     * ��һ��
     */
    Channel *getNext() {
        return _next;
    }

private:
    uint32_t _id;      // channel id
    void *_args;    // �ش�����
    IPacketHandler *_handler;
    int64_t _expireTime; // ����ʱ��

private:
    Channel *_prev;     // ��������
    Channel *_next;
};
}

#endif /*CONNECTION_H_*/
