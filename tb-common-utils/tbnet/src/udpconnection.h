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

#ifndef TBNET_UDPCONNECTION_H_
#define TBNET_UDPCONNECTION_H_

namespace tbnet {

class UDPConnection : public Connection {
    /*
     * ���캯��
     */
    UDPConnection(Socket *socket, IPacketStreamer *streamer, IServerAdapter *serverAdapter);

    /*
     * ���캯��
     */
    ~UDPConnection();

    /*
     * д������
     *
     * @return �Ƿ�ɹ�
     */
    bool writeData();

    /*
     * ��������
     *
     * @return ��������
     */
    bool readData();

};

}

#endif /*UDPCONNECTION_H_*/
