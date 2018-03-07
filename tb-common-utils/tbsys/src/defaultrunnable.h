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

#ifndef TBSYS_DEFAULT_RUNNABLE_H_
#define TBSYS_DEFAULT_RUNNABLE_H_

namespace tbsys {

/** 
 * @brief �߳�ִ�о����ҵ��ķ�װ��,ͬʱ��ά����һ���߳����ݣ�Ҳ���Խ�����
 * ����һ���̳߳���
 */
class CDefaultRunnable : public Runnable {

public:
    /**
     * ����
     */
    CDefaultRunnable(int threadCount = 1);
    
    /**
     * ����
     */
    virtual ~CDefaultRunnable();

    /**
     * �����߳���
     */
    void setThreadCount(int threadCount);
    
    /** 
     * start
     */
    void start();

    /**
     * stop
     */
    void stop();

    /**
     * wait
     */
    void wait();

protected:    
    CThread *_thread;
    int _threadCount;
    bool _stop;
};

}

#endif /*RUNNABLE_H_*/
