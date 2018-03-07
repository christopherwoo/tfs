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

#ifndef TBSYS_CONFIG_H
#define TBSYS_CONFIG_H

#include <string>
#include <ext/hash_map>
#include "stringutil.h"
#include "tblog.h"

//using namespace std;
//using namespace __gnu_cxx;

namespace tbsys {
/** 
* @brief ����string��hashֵ 
*/
    struct str_hash {
        size_t operator()(const std::string& str) const {
            return __gnu_cxx::__stl_hash_string(str.c_str());
        }
    };
    /** 
     * @brief �ַ����Ƚ�
     */
    struct char_equal {
        bool operator()(const char* s1, const char* s2) const {
            return strcmp(s1, s2) == 0;
        }
    };
    typedef __gnu_cxx::hash_map<std::string, std::string, str_hash> STR_STR_MAP;
    typedef STR_STR_MAP::iterator STR_STR_MAP_ITER;
    typedef __gnu_cxx::hash_map<std::string, STR_STR_MAP*, str_hash> STR_MAP;
    typedef STR_MAP::iterator STR_MAP_ITER;
    
    #define TBSYS_CONFIG tbsys::CConfig::getCConfig()
    
    /** 
     * @brief ���������ļ�,������������key-value����ʽ�洢���ڴ���
     */
    class           CConfig {
        public:
            CConfig();
            ~CConfig();
            
            // ����һ���ļ�
            int load(const char *filename);
            // ȡһ���ַ���
            const char *getString(const char *section, const std::string& key, const char *d = NULL);
            // ȡһstring�б�
            std::vector<const char*> getStringList(const char *section, const std::string& key);
            // ȡһ������
            int getInt(char const *section, const std::string& key, int d = 0);
            // ȡһ�����б�
            std::vector<int> getIntList(const char *section, const std::string& key);
            // ȡһsection�����е�key
            int getSectionKey(const char *section, std::vector<std::string> &keys);
            // �õ�����section������
            int getSectionName(std::vector<std::string> &sections);
            // �����������ļ��ַ���
            std::string toString();
            // �õ���̬ʵ��
            static CConfig& getCConfig();
            
        private:
            // ����map
            STR_MAP m_configMap;
            
        private:
            // �����ַ���
            int parseValue(char *str, char *key, char *val);
            char *isSectionName(char *str);     
    };
}

#endif
