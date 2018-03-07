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

#ifndef TBSYS_LOG_H
#define TBSYS_LOG_H

#include <stdarg.h>
#include <time.h>
#include <stdio.h>
#include <strings.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
#include <deque>
#include <string>
#include <pthread.h>
#include <sys/time.h>

#define TBSYS_LOG_LEVEL_ERROR 0
#define TBSYS_LOG_LEVEL_WARN  1
#define TBSYS_LOG_LEVEL_INFO  2
#define TBSYS_LOG_LEVEL_DEBUG 3
#define TBSYS_LOG_LEVEL(level) TBSYS_LOG_LEVEL_##level, __FILE__, __LINE__, __FUNCTION__
#define TBSYS_LOG_NUM_LEVEL(level) level, __FILE__, __LINE__, __FUNCTION__
#define TBSYS_LOGGER tbsys::CLogger::_logger
#define TBSYS_PRINT(level, ...) TBSYS_LOGGER.logMessage(TBSYS_LOG_LEVEL(level), __VA_ARGS__)
#define TBSYS_LOG_BASE(level, ...) (TBSYS_LOG_LEVEL_##level>TBSYS_LOGGER._level) ? (void)0 : TBSYS_PRINT(level, __VA_ARGS__) 
#define TBSYS_LOG(level, _fmt_, args...) ((TBSYS_LOG_LEVEL_##level>TBSYS_LOGGER._level) ? (void)0 : TBSYS_LOG_BASE(level, "[%ld] " _fmt_, pthread_self(), ##args))
#define TBSYS_LOG_US(level, _fmt_, args...) \
  ((TBSYS_LOG_LEVEL_##level>TBSYS_LOGGER._level) ? (void)0 : TBSYS_LOG_BASE(level, "[%ld][%ld][%ld] " _fmt_, \
                                                            pthread_self(), tbsys::CLogger::get_cur_tv().tv_sec, \
                                                            tbsys::CLogger::get_cur_tv().tv_usec, ##args))

namespace tbsys {
using std::deque;
using std::string;

/** 
* @brief �򵥵���־ϵͳ 
*/
class           CLogger {
public:
    CLogger();
    ~CLogger();
    /** 
     * @brief 
     * 
     * @param filename
     * @param fmt
     */
    void rotateLog(const char *filename, const char *fmt = NULL);
    /** 
     * @brief ����־����д���ļ�
     * 
     * @param level ��־�ļ���
     * @param file  ��־�������ڵ��ļ�
     * @param line  ��־�������ڵ��ļ����к�
     * @param function д����־���ݵĺ�������
     * @param fmt
     * @param ...
     */
    void logMessage(int level, const char *file, int line, const char *function, const char *fmt, ...);
    /** 
     * @brief ������־�ļ���
     * 
     * @param level DEBUG|WARN|INFO|ERROR
     */
    void setLogLevel(const char *level);
    /** 
     * @brief ������־�ļ�������
     * 
     * @param filename ��־�ļ�������
     */
    void setFileName(const char *filename, bool flag = false);
    /** 
     * @brief ����ļ��Ƿ��Ѿ���,��׼���,��������ض���
     */
    void checkFile();
    void setCheck(int v) {_check = v;}
    /** 
     * @brief ������־�ļ��ļ��Ĵ�С,�ﵽmaxFileSize���´�һ���ļ�
     * ��������ô����־ϵͳ�������־����
     * 
     * @param maxFileSize ��־�ļ��Ĵ�С
     */
    void setMaxFileSize( int64_t maxFileSize=0x40000000);
    /** 
     * @brief �������maxFileIndex����־�ļ�������maxFileIndex����־�ļ�
     * �ᰴʱ���Ⱥ�ɾ��,��������������־ϵͳ�ᰴʱ���Ⱥ�����ͳ��
     * 
     * @param maxFileIndex �����ļ���������
     */
    void setMaxFileIndex( int maxFileIndex= 0x0F);

    static inline struct timeval get_cur_tv()
    {
      struct timeval tv;
      gettimeofday(&tv, NULL);
      return tv;
    };

private:
    int _fd;
    char *_name;
    int _check;
    size_t _maxFileIndex;
    int64_t _maxFileSize;
    bool _flag;

public:
    static CLogger _logger;
    int _level;

private:
    std::deque<std::string> _fileList;
    static const char *const _errstr[];   
    pthread_mutex_t _fileSizeMutex;
    pthread_mutex_t _fileIndexMutex; 
};

}
#endif
