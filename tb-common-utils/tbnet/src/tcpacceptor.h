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

#ifndef TBNET_TCPACCEPTOR_H_
#define TBNET_TCPACCEPTOR_H_

namespace tbnet {

class TCPAcceptor : public IOComponent {

public:
    /**
    * ���캯������Transport���á�
    *
    * @param  owner:    ��������
    * @param  socket:   Socket����
    * @param streamer:   ���ݰ���˫��������packet����������������
    * @param serverAdapter:  ���ڷ������ˣ���Connection��ʼ����Channel����ʱ�ص�ʱ��
    */
    TCPAcceptor(Transport *owner, Socket *socket,
                IPacketStreamer *streamer, IServerAdapter *serverAdapter);

    /*
     * ��ʼ��
     *
     * @return �Ƿ�ɹ�
     */
    bool init(bool isServer = false);

    /**
    * �������ݿɶ�ʱ��Transport����
    *
    * @return �Ƿ�ɹ�, true - �ɹ�, false - ʧ�ܡ�
    */
    bool handleReadEvent();

    /**
     * ��accept��û��д�¼�
     */
    bool handleWriteEvent() {
        return true;
    }

    /*
     * ��ʱ���
     *
     * @param    now ��ǰʱ��(��λus)
     */
    void checkTimeout(int64_t now);

private:
    IPacketStreamer *_streamer;      // ���ݰ�������
    IServerAdapter  *_serverAdapter; // ������������
};
}

#endif /*TCPACCEPTOR_H_*/
