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

#ifndef TBSYS_MONITOR_H
#define TBSYS_MONITOR_H
#include <iostream>
#include "Lock.h"
#include "Cond.h"

//using namespace std;

namespace tbutil
{
/** 
* @brief �������һ��ģ���࣬����ҪMutex��RecMutex��ģ�����,�������һ��
* ���ڱ����ٽ�����ͬ������,�ͻ�����һ�������ٽ�����ֻ��һ���߳��ڻ
* ��������������ٽ����ڹ����߳�,��������һ���߳̾��ܽ����ٽ������ڶ����߳̾�
* ���˳��ٽ���,�������ٽ����ڹ����Լ�,�����������ԭ�����̶߳��ᱻ���ѣ�����
* ִ��ԭ��������
*/
template <class T>
class Monitor
{
public:

    typedef LockT<Monitor<T> > Lock;
    typedef TryLockT<Monitor<T> > TryLock;

    Monitor();
    ~Monitor();

    /** 
     * @brief �������������ס����������������ѱ�������߳���ס������
     * ���õ��߳̾ͻ����ֱ�����������Ϊֹ���ڵ��÷���ʱ��������ѱ�����ס
     */
    void lock() const;
    /** 
     * @brief ����������������ļ����������������߳��ڵȴ���������
     * (Ҳ����������lock ������)������һ���̻߳ᱻ���ѣ�����ס�����
     * 
     * @return 
     */
    void unlock() const;
    /** 
     * @brief �������������ס������������������ã����þ���ס�������
     * ����true�����������ѱ�������߳���ס�����÷���false 
     */
    bool tryLock() const;

    /** 
     * @brief ����������𷢳����õ��̣߳�ͬʱ�ͷż�����ϵ����������߳̿��ܵ���notify
     * ��notifyAll ��������wait �����й�����߳�.��wait ���÷���ʱ��������ر���ס,
     * ��������̻߳�ָ�ִ�� 
     * @return 
     */
    bool wait() const;
    /** 
     * @brief �������������������̣߳�ֱ��ָ����ʱ�����š�����������
     * �̵߳���notify ��notifyAll���ڷ�����ʱ֮ǰ���ѹ�����̣߳�
     * ������÷���true��������ر���ס��������ָ̻߳�ִ�С������
     * ������ʱ����������false
     * @param Time
     * 
     * @return 
     */
    bool timedWait(const Time&) const;
    /** 
     * @brief �����������Ŀǰ��wait �����й����һ���̡߳�����ڵ���
     * notify ʱû���������̣߳�֪ͨ�ͻᶪʧ(Ҳ����˵�����û���߳�
     * �ܱ����ѣ���notify �ĵ��ò��ᱻ��ס)
     */
    void notify();
    /** 
     * @brief �����������Ŀǰ��wait �����й���������̡߳���notify һ
     * ���������ʱû�й�����̣߳���notifyAll �ĵ��þͻᶪʧ 
     */
    void notifyAll();

private:

    Monitor(const Monitor&);
    Monitor& operator=(const Monitor&);

    void notifyImpl(int) const;

    mutable Cond _cond;
    T _mutex;
    mutable int _nnotify;
};

template <class T> 
Monitor<T>::Monitor() :
    _nnotify(0)
{
}

template <class T> 
Monitor<T>::~Monitor()
{
}

template <class T> inline void
Monitor<T>::lock() const
{
    _mutex.lock();
    if(_mutex.willUnlock())
    {
        _nnotify = 0;
    }
}

template <class T> inline void
Monitor<T>::unlock() const
{
    if(_mutex.willUnlock())
    {
        notifyImpl(_nnotify);
    }
    _mutex.unlock();
}

template <class T> inline bool
Monitor<T>::tryLock() const
{
    bool result = _mutex.tryLock();
    if(result && _mutex.willUnlock())
    {
        _nnotify = 0;
    }
    return result;
}

template <class T> inline bool 
Monitor<T>::wait() const
{
    notifyImpl(_nnotify);
#ifdef _NO_EXCEPTION
    const bool bRet = _cond.waitImpl(_mutex);
    _nnotify = 0;
    return bRet;
#else
    try
    {
        _cond.waitImpl(_mutex);
    }
    catch(...)
    {
        _nnotify = 0;
        throw;
    }

    _nnotify = 0;
#endif
    return true;
}

template <class T> inline bool
Monitor<T>::timedWait(const Time& timeout) const
{
    notifyImpl(_nnotify);
#ifdef _NO_EXCEPTION
    const bool rc = _cond.timedWaitImpl(_mutex, timeout);
    _nnotify = 0;
    return rc;
#else
    try
    {
        _cond.timedWaitImpl(_mutex, timeout);
    }
    catch(...)
    {
        _nnotify = 0;
        throw;
    }
    _nnotify = 0;
#endif
    return true;
}

template <class T> inline void
Monitor<T>::notify()
{
    if(_nnotify != -1)
    {
        ++_nnotify;
    }
}

template <class T> inline void
Monitor<T>::notifyAll()
{
    _nnotify = -1;
}


template <class T> inline void
Monitor<T>::notifyImpl(int nnotify) const
{
    if(nnotify != 0)
    {
        if(nnotify == -1)
        {
            _cond.broadcast();
            return;
        }
        else
        {
            while(nnotify > 0)
            {
                _cond.signal();
                --nnotify;
            }
        }
    }
}
}//end namespace
#endif
