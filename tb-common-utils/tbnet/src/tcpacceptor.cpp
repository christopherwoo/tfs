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

#include "tbnet.h"

namespace tbnet {
/**
 * ���캯������Transport���á�
 *
 * @param  owner:    ��������
 * @param  host:   ����ip��ַ��hostname
 * @param port:   �����˿�
 * @param streamer:   ���ݰ���˫��������packet����������������
 * @param serverAdapter:  ���ڷ������ˣ���Connection��ʼ����Channel����ʱ�ص�ʱ��
 */
TCPAcceptor::TCPAcceptor(Transport *owner, Socket *socket,
                         IPacketStreamer *streamer, IServerAdapter *serverAdapter) : IOComponent(owner, socket) {
    _streamer = streamer;
    _serverAdapter = serverAdapter;
}

/*
 * ��ʼ��, ��ʼ����
 */
bool TCPAcceptor::init(bool isServer) {
    _socket->setSoBlocking(false);
    return ((ServerSocket*)_socket)->listen();
}

/**
* �������ݿɶ�ʱ��Transport����
*
* @return �Ƿ�ɹ�
*/
bool TCPAcceptor::handleReadEvent() {
    Socket *socket;
    while ((socket = ((ServerSocket*)_socket)->accept()) != NULL) {
        //TBSYS_LOG(INFO, "�������ӽ���, fd: %d", socket->getSocketHandle());
        // TCPComponent, �ڷ�������
        TCPComponent *component = new TCPComponent(_owner, socket, _streamer, _serverAdapter);

        if (!component->init(true)) {
            delete component;
            return true;
        }

        // ���뵽iocomponents�У���ע��ɶ���socketevent��
        _owner->addComponent(component, true, false);
    }

    return true;
}

/*
 * ��ʱ���
 *
 * @param    now ��ǰʱ��(��λus)
 */
void TCPAcceptor::checkTimeout(int64_t now) {}
}
