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

#ifndef TBSYS_QUEUE_THREAD_H
#define TBSYS_QUEUE_THREAD_H

#include <queue>

//using namespace std;

namespace tbsys {
        
	/** 
	 * @brief Queue �����̳߳�
	 */
    class CQueueThread : public CDefaultRunnable {
        public:
            /* ���캯�� */
            CQueueThread(int threadCount, IQueueHandler *handler, void *args);
            /* �������� */
            ~CQueueThread(void);
            /* д������ */
            int writeData(void *data, int len);
            /* ֹͣ */
            void stop();
            /* ������ں��� */
            void run(CThread *thread, void *args);
                   
        private:
            typedef struct data_pair {
                char *data;
                int len;
            } data_pair;
            // queue
            std::queue<data_pair*> _queue;            
            
        protected:
            // �߳���
            CThreadCond _mutex;
            // ������
            IQueueHandler *_handler;
            // ��������
            void *_args;
    };
}

#endif

//////////////////END
