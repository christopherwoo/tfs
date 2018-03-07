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

#ifndef TBSYS_MEMORY_HPP_
#define TBSYS_MEMORY_HPP_
#include <new>
#include <stddef.h>

namespace tbsys
{
/**
 * ��new�ؼ���ת���ɺ���
 * @see 
 * @return �´�����Type��Ķ���(�ɹ�)/NULL(ʧ��)
 */
template <typename Type> inline Type *gNew()
{
    Type *Pointer = NULL;
#ifdef _NO_EXCEPTION
    Pointer = new Type;
#else
    try
    {
        Pointer = new Type;
    }
    catch (...)
    {
        Pointer = NULL;
    }
#endif // _NO_EXCEPTION
    return Pointer;
}

/**
 * ��new []�ؼ���ת���ɺ���
 * @param uiItemNum(unsigned): ��������Ĵ�С
 * @see 
 * @return ����uiItemNum�������Ķ�������(�ɹ�)/NULL(ʧ��)
 */
template <typename Type> inline Type *gNewA(unsigned uiItemNum)
{
    Type *Pointer = NULL;
#ifdef _NO_EXCEPTION
        Pointer = new Type[uiItemNum];
#else
    try
    {
        Pointer = new Type[uiItemNum];
    }
    catch (...)
    {
        Pointer = NULL;
    }
#endif // _NO_EXCEPTION
    return Pointer;
}

// if not use the default construct, please use this macro, but is can't reference
#ifdef _NO_EXCEPTION
/**
 * �����в����Ĺ��캯�����������
 * @param Pointer: �������������ֵΪ�´�����Class��Ķ���
 * @param Class: �贴�����������
 * @param ...: ���캯�������б�
 * @see 
 * @return void
 */
#define ARG_NEW(Pointer, Class, ...) \
    do \
    { \
        Pointer = new Class(__VA_ARGS__); \
    } \
    while (0)
#else
#define ARG_NEW(Pointer, Class, ...) \
    do \
    { \
        try \
        { \
            Pointer = new Class(__VA_ARGS__); \
        } \
        catch (...) \
        { \
            Pointer = NULL; \
        } \
    } \
    while (0)
#endif

/**
 * ��placement newת���ɺ���
 * @param p(void *): ���������ڴ��ַ
 * @see 
 * @return Type���Ͷ���(�ɹ�)/NULL(ʧ��)
 */
template <typename Type> inline Type *gConstruct(void *p)
{
    Type *Pointer = NULL;
#ifdef _NO_EXCEPTION
    Pointer = new (p) Type;
#else
    try
    {
        Pointer = new (p) Type;
    }
    catch (...)
    {
        Pointer = NULL;
    }
#endif // _NO_EXCEPTION
    return Pointer;
}

/*
 * if not use the default construct, please use this macro, but is can't reference
 */
#ifdef _NO_EXCEPTION
/**
 * ��װ���캯�����쳣�����ṩ�������
 * @param Pointer: �������������ֵΪ�´�����Class��Ķ���
 * @param Class: �贴�����������
 * @param Memory: ���������ڴ��ַ
 * @param ...: �������Ĳ����б�
 * @see 
 * @return 
 */
#define CONSTRUCT(Pointer, Class, Memory, ...) \
    do \
    { \
        Pointer = new (Memory) Class(__VA_ARGS__); \
    } \
    while (0)
#else
#define CONSTRUCT(Pointer, Class, Memory, ...) \
    do \
    { \
        try \
        { \
            Pointer = new (Memory) Class(__VA_ARGS__); \
        } \
        catch (...) \
        { \
            Pointer = NULL; \
        } \
    } \
    while (0)
#endif // _NO_EXCEPTION

#ifdef _NO_EXCEPTION
/**
 * ����Ĭ�Ϲ��캯��������󣬷�װ�쳣
 * @param Pointer: �������������ֵΪ�´�����Class��Ķ���
 * @param Class: �贴�����������
 * @see 
 * @return 
 */
#define FRIEND_NEW(Pointer, Class) \
    do \
    { \
        Pointer = new Class; \
    } \
    while (0)
#else
#define FRIEND_NEW(Pointer, Class) \
    do \
    { \
        try \
        { \
            Pointer = new Class; \
        } \
        catch (...) \
        { \
            Pointer = NULL; \
        } \
    } \
    while (0)
#endif

#ifdef _NO_EXCEPTION
/**
 * ����Ĭ�Ϲ��캯�������������飬��װ�쳣
 * @param Pointer: �������������ֵΪ�´�����Class��Ķ�������
 * @param Class: �贴���������������
 * @param Num: �贴����������ĳ���
 * @see 
 * @return void
 */
#define FRIEND_NEW_A(Pointer, Class, Num) \
    do \
    { \
        Pointer = new Class [Num]; \
    } \
    while (0)
#else
#define FRIEND_NEW_A(Pointer, Class, Num) \
    do \
    { \
        try \
        { \
            Pointer = new Class [Num]; \
        } \
        catch (...) \
        { \
            Pointer = NULL; \
        } \
    } \
    while (0)
#endif

/**
 * ��delete�ؼ���ת���ɺ���������װ�쳣
 * @param p(Type *): Ҫ�ͷŵĶ����ַ
 * @see 
 * @return void
 */
template <typename Type> inline void gDelete(Type *&rp)
{
    if (rp != NULL)
    {
#ifdef _NO_EXCEPTION
        delete rp;
        rp = NULL;
#else
        try
        {
            delete rp;
            rp = NULL;
        }
        catch (...)
        {

        }
#endif // _NO_EXCEPTION
        rp = NULL;
    }
}

/**
 * ��delete []�ؼ���ת���ɺ���������װ�쳣
 * @param p(Type *): Ҫ�ͷŵĶ��������ַ
 * @see 
 * @return void
 */
template <typename Type> inline void gDeleteA(Type *&rp)
{
    if (rp != NULL)
    {
#ifdef _NO_EXCEPTION
        delete [] rp;
        rp = NULL;
#else
        try
        {
            delete [] rp;
            rp = NULL;
        }
        catch (...)
        {

        }
#endif // _NO_EXCEPTION
        rp = NULL;
    }
}

/**
 * �Ѷ������������ת����ͨ�ú�������װ�쳣
 * @param p(Type *): ��Ҫ�������Ķ����ַ
 * @see 
 * @return void
 */
template <typename Type> inline void gDestruct(Type *p)
{
#ifdef _NO_EXCEPTION
    p->~Type();
#else
    try
    {
        p->~Type();
    }
    catch (...)
    {

    }
#endif // _NO_EXCEPTION
}

/**
 * 
 * @param p(Type *): ��Ҫ�ͷŵ��ڴ���ַ
 * @see 
 * @return void
 */
template <typename Type> inline void gFree(Type *&rp)
{
    if (rp != NULL)
    {
        free(rp);
        rp = NULL;
    }
}

#ifdef _NO_EXCEPTION
/**
 * �ͷŶ��󣬷�װ�쳣
 * @param Pointer: ��Ҫ���ͷŵĶ����ַ
 * @see 
 * @return void
 */
#define FRIEND_DEL(Pointer) \
    do \
    { \
        if (Pointer != NULL) \
        { \
            delete Pointer; \
            Pointer = NULL; \
        } \
    } \
    while (0)
#else
#define FRIEND_DEL(Pointer) \
    do \
    { \
        if (Pointer != NULL) \
        { \
            try \
            { \
                delete Pointer; \
                Pointer=NULL;\
            } \
            catch (...) \
            { \
                 \
            } \
            Pointer = NULL; \
        } \
    } \
    while (0)
#endif

#ifdef _NO_EXCEPTION
/**
 * �ͷŶ������飬��װ�쳣
 * @param Pointer: ��Ҫ���ͷŵĶ��������ַ
 * @see 
 * @return void
 */
#define FRIEND_DEL_A(Pointer) \
    do \
    { \
        if (Pointer != NULL) \
        { \
            delete [] Pointer; \
            Pointer = NULL; \
        } \
    } \
    while (0)
#else
#define FRIEND_DEL_A(Pointer) \
    do \
    { \
        if (Pointer != NULL) \
        { \
            try \
            { \
                delete [] Pointer; \
                Pointer = NULL;\
            } \
            catch (...) \
            { \
                 \
            } \
            Pointer = NULL; \
        } \
    } \
    while (0)
#endif

}//end namespace
#endif // MEMORY_HPP_
