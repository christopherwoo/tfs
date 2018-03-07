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

#ifndef TBNET_TRANSPORT_H_
#define TBNET_TRANSPORT_H_

#include <sys/ptrace.h>

namespace tbnet {

class Transport : public tbsys::Runnable {

public:
    /*
     * ���캯��
     */
    Transport();

    /*
     * ���캯��
     */
    ~Transport();

    /*
     * ������㣬���������̣߳�һ�����ڶ���һ����д��
     *
     * @return �Ƿ�ɹ�, true - �ɹ�, false - ʧ�ܡ�
     */
    bool start();

    /*
     * ֹͣ��ͣ����д�̣߳������١�
     *
     * @return �Ƿ�ɹ�, true - �ɹ�, false - ʧ�ܡ�
     */
    bool stop();

    /*
     * �ȴ��߳���ȫ�˳���
     *
     * @return �Ƿ�ɹ�, true - �ɹ�, false - ʧ�ܡ�
     */
    bool wait();

    /*
     * �̵߳����к�����ʵ��Runnable�ӿ��еĺ���
     *
     * @param arg: ����ʱ�������
     */
    void run(tbsys::CThread *thread, void *arg);

    /*
     * ��һ�������˿ڡ�
     *
     * @param spec: ��ʽ [upd|tcp]:ip:port
     * @param streamer: ���ݰ���˫��������packet����������������
     * @param serverAdapter: ���ڷ������ˣ���Connection��ʼ����Channel����ʱ�ص�ʱ��
     * @return IO���һ�������ָ��
     */
    IOComponent *listen(const char *spec, IPacketStreamer *streamer, IServerAdapter *serverAdapter);

    /*
     * ����һ��Connection�����ӵ�ָ���ĵ�ַ�������뵽Socket�ļ����¼��С�
     *
     * @param spec: ��ʽ [upd|tcp]:ip:port
     * @param streamer: ���ݰ���˫��������packet����������������
     * @param autoReconn: �Ƿ�����
     * @return  ����һ��Connectoion����ָ��
     */
    Connection *connect(const char *spec, IPacketStreamer *streamer, bool autoReconn = false);

    /*
     * �����Ͽ�
     */
    bool disconnect(Connection *conn);

    /*
     * ���뵽iocomponents��
     *
     * @param  ioc: IO���
     * @param  readOn: ��ʼ���Ѷ��¼���
     * @param  writeOn: ��ʼ����д�¼���
     */
    void addComponent(IOComponent *ioc, bool readOn, bool writeOn);

    /*
     * ��iocomponents��ɾ����
     *
     * @param ioc: IO���
     */
    void removeComponent(IOComponent *ioc);
    
    /**
     * �Ƿ�Ϊstop
     */
    bool* getStop();

private:
    /*
     * ��[upd|tcp]:ip:port�ֿ�����args��
     *
     * @param src: Դ��ʽ
     * @param args: Ŀ������
     * @param   cnt: ������������
     * @return  ���ص������и���
     */
    int parseAddr(char *src, char **args, int cnt);

    /*
     * socket event �ļ��
     */
    void eventLoop(SocketEvent *socketEvent);

    /*
     * ��ʱ���
     */
    void timeoutLoop();

    /*
     * �ͷű���
     */
    void destroy();

private:

    EPollSocketEvent _socketEvent;      // ��дsocket�¼�
    tbsys::CThread _readWriteThread;    // ��д�����߳�
    tbsys::CThread _timeoutThread;      // ��ʱ����߳�
    bool _stop;                         // �Ƿ�ֹͣ

    IOComponent *_delListHead, *_delListTail;  // �ȴ�ɾ����IOComponent����
    IOComponent *_iocListHead, *_iocListTail;   // IOComponent����
    bool _iocListChanged;                       // IOComponent���ϱ��Ĺ�
    int _iocListCount;
    tbsys::CThreadMutex _iocsMutex;
};
}

#endif /*TRANSPORT_H_*/
