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

#ifndef TBSYS_EVENTHANDLER_H
#define TBSYS_EVENTHANDLER_H

namespace tbutil
{
class ThreadPool;
/** 
 * @brief ThreadPoolWorkItem �߳��������Item����,��ӵ��execute���鷽��
 * Ҫʵ����ThreadPoolWorkItem�࣬����̳в�ʵ��execute����
 */
class ThreadPoolWorkItem 
{
public:
      virtual ~ThreadPoolWorkItem(){}
      virtual void destroy( )=0;
      virtual void execute( const ThreadPool* ) = 0;
};
}
#endif
