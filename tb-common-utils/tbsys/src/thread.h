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

#ifndef TBSYS_THREAD_H_
#define TBSYS_THREAD_H_

#include <linux/unistd.h>

namespace tbsys {

/** 
 * @brief ��linux�̼߳򵥷�װ 
 */
class CThread {

public:
    /**
     * ���캯��
     */
    CThread() {
        tid = 0;
        pid = 0;
    }

    /**
     * ��һ���̣߳���ʼ����
     */
    void start(Runnable *r, void *a) {
        runnable = r;
        args = a;
        pthread_create(&tid, NULL, CThread::hook, this);
    }

    /**
     * �ȴ��߳��˳�
     */
    void join() {
        if (tid) {
            pthread_join(tid, NULL);
            tid = 0;
            pid = 0;
        }
    }

    /**
     * �õ�Runnable����
     * 
     * @return Runnable
     */
    Runnable *getRunnable() {
        return runnable;
    }

    /**
     * �õ��ص�����
     * 
     * @return args
     */
    void *getArgs() {
        return args;
    }
    
    /***
     * �õ��̵߳Ľ���ID
     */
    int getpid() {
        return pid;
    }

    /**
     * �̵߳Ļص�����
     * 
     */

    static void *hook(void *arg) {
        CThread *thread = (CThread*) arg;
        thread->pid = gettid();

        if (thread->getRunnable()) {
            thread->getRunnable()->run(thread, thread->getArgs());
        }

        return (void*) NULL;
    }
    
private:    
    /**
     * �õ�tid��
     */
    #ifdef _syscall0
    static _syscall0(pid_t,gettid)
    #else
    static pid_t gettid() { return syscall(__NR_gettid);}
    #endif

private:
    pthread_t tid;      // pthread_self() id
    int pid;            // �̵߳Ľ���ID
    Runnable *runnable;
    void *args;
};

}

#endif /*THREAD_H_*/
