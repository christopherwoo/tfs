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

#ifndef TBNET_HTTP_PACKET_STREAMER_H
#define TBNET_HTTP_PACKET_STREAMER_H

namespace tbnet {


class HttpPacketStreamer : public DefaultPacketStreamer {
public:
    /*
     * ���캯��
     */
    HttpPacketStreamer();
    /*
     * ���캯��
     */
    HttpPacketStreamer(IPacketFactory *factory);
    /*
     * ���ݰ���Ϣ������
     */
    bool getPacketInfo(DataBuffer *input, PacketHeader *header, bool *broken);
    /*
     * ����_httpPacketCode
     */
    void setHttpPacketCode(int code) {
        _httpPacketCode = code;
    }
private:
    int _httpPacketCode;
};

/**
 * packet��factory, ȱʡ��httpd packet factory
 *
 * pcode = 1 �������
 * pcode = 0 ����Ӧ��
 */
class DefaultHttpPacketFactory : public IPacketFactory {
public:
    Packet *createPacket(int pcode) {
        if (pcode == 1) {
            return new HttpRequestPacket();
        } else {
            return new HttpResponsePacket();
        }
    }
};

}

#endif

