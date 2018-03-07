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

#ifndef TBNET_CONTROL_PACKET_H_
#define TBNET_CONTROL_PACKET_H_
#ifndef UNUSED
#define UNUSED(v) ((void)(v))
#endif

namespace tbnet {

class ControlPacket : public Packet {
public:
    enum {
        CMD_BAD_PACKET = 1,
        CMD_TIMEOUT_PACKET,
        CMD_DISCONN_PACKET
    };

    static ControlPacket BadPacket;
    static ControlPacket TimeoutPacket;
    static ControlPacket DisconnPacket;

public:
    /*
     * ���캯��, ��������
     */
    ControlPacket(int c) : _command(c) {}

    /*
     * �Ƿ����ݰ�
     */
    bool isRegularPacket() {
        return false;
    }

    void free() {}

    /*
     * ��������ݰ��ĳ���
     */
    void countDataLen() {}

    /*
     * ��װ
     */
    bool encode(DataBuffer *output) {
      UNUSED(output);
        return false;
    }

    /*
     * �⿪
     */
    bool decode(DataBuffer *input, PacketHeader *header) {
      UNUSED(input);
      UNUSED(header);
        return false;
    }

    /*
     * �õ�����
     */
    int getCommand() {
        return _command;
    }

private:
    int _command;
};

}

#endif /*PACKET_H_*/
