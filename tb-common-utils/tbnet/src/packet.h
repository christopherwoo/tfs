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

#ifndef TBNET_PACKET_H_
#define TBNET_PACKET_H_

namespace tbnet {

#define TBNET_PACKET_FLAG 0x416e4574  // AnEt

class PacketHeader {
public:
    uint32_t _chid;         // ͨ��ID
    int _pcode;             // ���ݰ�����
    int _dataLen;           // ���ݰ�body����(��ͷ��Ϣ��)
};

class Packet {
    friend class PacketQueue;

public:
    /*
     * ���캯��, ��������
     */
    Packet();

    /*
     * ��������
     */
    virtual ~Packet();

    /*
     * ����ChannelID
     */
    void setChannelId(uint32_t chid) {
        _packetHeader._chid = chid;
    }

    /*
     * �õ�Channel ID
     */
    uint32_t getChannelId() const {
        return _packetHeader._chid;
    }

    /*
     * ����PCode
     */
    void setPCode(int pcode) {
        _packetHeader._pcode = pcode;
    }

    /*
     * �õ�PCode
     */
    int getPCode() const {
        return _packetHeader._pcode;
    }

    /*
     * �õ����ݰ�header info
     */
    PacketHeader *getPacketHeader() {
        return &_packetHeader;
    }

    /*
     * �������ݰ�header info
     */
    void setPacketHeader(PacketHeader *header) {
        if (header) {
            memcpy(&_packetHeader, header, sizeof(PacketHeader));
        }
    }

    /*
     * �ͷ��Լ�
     */
    virtual void free() {
        delete this;
    }

    /*
     * �Ƿ����ݰ�
     */
    virtual bool isRegularPacket() {
        return true;
    }

    /*
     * ��װ
     *
     * @param output: Ŀ��buffer
     * @return �Ƿ�ɹ�
     */
    virtual bool encode(DataBuffer *output) = 0;

    /*
     * �⿪
     *
     * @param input: Դbuffer
     * @param header: ���ݰ�header
     * @return �Ƿ�ɹ�
     */
    virtual bool decode(DataBuffer *input, PacketHeader *header) = 0;

    /*
     * ��ʱʱ��
     */
    int64_t getExpireTime() const {
        return _expireTime;
    }

    /*
     * ���ù���ʱ��
     *
     * @param milliseconds ������, 0Ϊ��������
     */
    void setExpireTime(int milliseconds);

    /*
     * ����Channel
     */
    void setChannel(Channel *channel);

    /*
     * �õ�Channel
     */
    Channel *getChannel() const {
        return _channel;
    }

    /*
     * �õ�next
     */
    Packet *getNext() const {
        return _next;
    }

protected:
    PacketHeader _packetHeader; // ���ݰ���ͷ��Ϣ
    int64_t _expireTime;        // ����ʱ��
    Channel *_channel;

    Packet *_next;              // ����packetqueue����
};

}

#endif /*PACKET_H_*/
