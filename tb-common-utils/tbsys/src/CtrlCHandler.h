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

#ifndef TBSYS_CTRL_C_HANDLER_H
#define TBSYS_CTRL_C_HANDLER_H

#include "Exception.h"

namespace tbutil
{
typedef void (*CtrlCHandlerCallback)(int);

/** 
 * @brief CtrlCHanler ���ڴ���Ctrl+C ���������Ƶķ���C++ ���̵��ź�
 * ����һʱ�̣���һ��������ֻ���� һ��CtrlCHandler ʵ��
 */
class CtrlCHandler
{
public:

/** 
* @brief ��һ���ص���������һ��ʵ��
* 
* @param CtrlCHandlerCallback
*/
    CtrlCHandler(CtrlCHandlerCallback = 0);
    ~CtrlCHandler();

    /** 
     * @brief �����µĻص�����
     * 
     * @param callback 
     */
    void setCallback(CtrlCHandlerCallback callback);
    /** 
     * @brief ��õ�ǰ�ص�����
     * 
     * @return 
     */
    CtrlCHandlerCallback getCallback() const;
};


/** 
 * @brief CtrlCHandlerʵ������Ѿ����ھͻ��׳��쳣
 */
class CtrlCHandlerException : public Exception
{ 
public:
 
    CtrlCHandlerException(const char*, int);
    virtual std::string _name() const;
    virtual Exception* _clone() const;
    virtual void _throw() const;
};
}//end namespace
#endif
