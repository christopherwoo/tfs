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

#ifndef TBSYS_EXCEPTION_H
#define TBSYS_EXCEPTION_H
#include <exception>
#include <string>
#include <ostream>

#include "tbsys.h"

//using namespace std;

namespace tbutil
{
/** 
* @brief Exception�Ƕ�std::exception����װ 
*/
class Exception : public std::exception
{
public:

    Exception();
    Exception(const char*, int);
    virtual ~Exception() throw();
    virtual std::string name() const;
    virtual void print(std::ostream&) const;
    virtual const char* what() const throw();
    virtual Exception* clone() const;
    virtual void _throw() const;
    const char* file() const;
    int line() const;
    
private:
    
    const char* _file;
    int _line;
    static const char* _name;
    mutable ::std::string _str; 
};

std::ostream& operator << (std::ostream& out, const Exception& ex);

/** 
 * @brief HandleΪ���쳣��
 */
class NullHandleException : public Exception
{
public:
    
    NullHandleException(const char*, int);
    virtual ~NullHandleException() throw();
    virtual std::string name() const;
    virtual Exception* clone() const;
    virtual void _throw() const;

private:
    static const char* _name;
};

/** 
 * @brief ���Ϸ������쳣��
 */
class IllegalArgumentException : public Exception
{
public:
    
    IllegalArgumentException(const char*, int);
    IllegalArgumentException(const char*, int, const std::string&);
    virtual ~IllegalArgumentException() throw();
    virtual std::string name() const;
    virtual void print(std::ostream&) const;
    virtual Exception* clone() const;
    virtual void _throw() const;

    std::string reason() const;

private:

    static const char* _name;
    std::string _reason;
};

/** 
 * @brief ϵͳ�����쳣��
 */
class SyscallException : public Exception
{
public:
    SyscallException( const char* , int );
    SyscallException(const char*, int, int);
    virtual std::string name() const;
    virtual void print(std::ostream&) const;
    virtual Exception* clone() const;
    virtual void _throw() const;

    int error() ;

    int _error;
    static const char* _name;
};
}//end namespace
#endif
