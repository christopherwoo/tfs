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

#ifndef TBSYS_RUNNABLE_H_
#define TBSYS_RUNNABLE_H_

namespace tbsys {

/** 
 * @brief Runnable��һ�������࣬��ӵ��һ��run���鷽��
 * ��Ҫ����Thread��  
 */
class Runnable {

public:
    /*
     * ����
     */
    virtual ~Runnable() {
    }
    /**
     * ������ں���
     */
    virtual void run(CThread *thread, void *arg) = 0;
};

}

#endif /*RUNNABLE_H_*/
