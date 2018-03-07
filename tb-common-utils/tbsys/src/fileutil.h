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

#ifndef TBSYS_FILE_UTIL_H
#define TBSYS_FILE_UTIL_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <errno.h>

namespace tbsys {

    #ifndef S_IRWXUGO
    # define S_IRWXUGO (S_IRWXU | S_IRWXG | S_IRWXO)
    #endif
    
   /** 
    * @brief ���ļ�Ŀ¼�Ļ������� 
    */
    class CFileUtil {
        public:
            /** �����༶Ŀ¼ */
            static bool mkdirs(char *szDirPath);
            /** �Ƿ�ΪĿ¼ */
            static bool isDirectory(const char *szDirPath);
            /** �Ƿ�ΪSymLink�ļ� */
            static bool isSymLink(const char *szDirPath);
    };
}

#endif

//////////////////END
