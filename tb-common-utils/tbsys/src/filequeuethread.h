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

#ifndef TBSYS_FILE_QUEUE_THREAD_H
#define TBSYS_FILE_QUEUE_THREAD_H

//using namespace std;

namespace tbsys {
	/** 
	 * @brief File Queue �����̳߳�
	 */
    class CFileQueueThread : public CDefaultRunnable {
        public:
            /** ���캯�� */
            CFileQueueThread(CFileQueue *queue, int threadCount, IQueueHandler *handler, void *args);
            /** �������� */
            ~CFileQueueThread(void);
            /** д������ */
            int writeData(void *data, int len);
            /** ֹͣ */
            void stop();
            /** ������ں��� */
            void run(CThread *thread, void *args);
            
        private:
            /** �߳���*/
            CThreadCond _mutex;
            /** ������*/
            IQueueHandler *_handler;
            /** ��������*/
            void *_args;
            /** file queue*/
            CFileQueue *_queue;
    };
}

#endif

//////////////////END
