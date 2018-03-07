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

#ifndef TBSYS_SERVICE_H
#define TBSYS_SERVICE_H
#include<string>
#include "Mutex.h"
#include "Monitor.h"
namespace tbutil
{
/** 
* @brief Service �Ƕ�linux/Unix�ػ����̺ͽ����������ڿ���̨ʱ���CtlC���ź�1��װ
* ����һ������ĵ�����,ʵ����ʱ����̳д��࣬��ʵ��run,destroy����,ͬʱService��
* �Խ��������͹رս��з�װ
*/
class Service
{
public:
    Service();
    virtual ~Service();

    /** 
     * @brief ɨ������������������Ƿ��б�����ѡ��ó�����Ϊϵͳ�������С�
     * ����һЩ����ѡ������ڹ������񡣾����ó���(deamon)ϵͳ��������,���ǰ��տ���̨��������
     * ����һ��CtrlCHandler ���Խ����ʵ����źŴ���
     * ����start ��Ա���������start ���ر�ʾʧ�ܵ�false�����˳� 
     * @param argc
     * @param argv[]
     * 
     * @return 
     */
    int main(int argc, char* argv[]);

    static Service* instance();    
    /** 
     * @brief �Ƿ����ػ�����(deamon)
     * 
     * @return 
     */
    bool service() const;
    /** 
     * @brief �źŴ���������������ʾ�յ����ź�,ʹ�ô�����û����ܵ��ô˺���
     * 
     * @param sig :�źŵı��
     * 
     * @return 
     */
    int handleInterrupt(int sig);

protected:
    /** 
     * @brief ��������ͨ��������Ƶķ���ֹͣ����
     * ���ô˺���ʱ�������shutdown
     */
    void stop();
    /** 
     * @brief �÷�������ʼ�رյĹ��� 
     * * ���ô˺���ʱ����ȴ�������ֹ������������һ��֪ͨ
     * @return 
     */
    int shutdown();
    /** 
     * @brief ��������ִ�����������������ɨ�����ṩ�Ĳ���������ʶ��������ѡ��
     * 
     * @param argc
     * @param argv[]
     * @param config
     * 
     * @return 
     */
    virtual int run( int argc , char*argv[], const std::string& config, std::string& errMsg)=0;
    /** 
     * @brief ���������յ��ź�ʱ����Ӧ�Ķ���,���統�յ�SIGINTʱ������ϵͳʹ�ù���
     * �����Դ�����رս���
     * 
     * @param sig
     * 
     * @return 
     */
    virtual int interruptCallback( int sig );
    /** 
     * @brief �ڽ��̹ر�ʱ,������ص���Դ
     * 
     * @return 
     */
    virtual bool destroy()=0;
    /** 
     * @brief ��ʾ�����а�����Ϣ
     */
    virtual void help();
    /** 
     * @brief ��ʾ��ǰ����汾��Ϣ
     */
    virtual void version();

    /** 
    * @brief �����źŴ�����Ϊ,�����Ժ�������źŷ���interruptCallback�����ᱻ���� 
    */
    void enableInterrupt();
    /** 
    * @brief �����źŴ�����Ϊ,�����Ժ�������źŷ���interruptCallback�������ᱻ���� 
    */
    void disableInterrupt();

private:
    /** 
     * @brief ����ǰ���̷����̨���� 
     * ��Ҫ������������Ϊ�ػ�������صĹ���
     * ����һ����̨�ӽ���,���ӽ��̳ɹ�����run����֮ǰ�������̲����˳�
     * ���ӽ��̵�pidд��pid�ļ���
     * �������øı��ӽ��̵Ĺ���Ŀ¼
     * �������ùر�û�õ��ļ�
     * @param argc
     * @param argv[]
     * 
     * @return 
     */
    int runDaemon( int argc ,char* argv[] );
    /** 
     * @brief �����ڵصȴ�����ر�
     * 
     * @return 
     */
    int waitForShutdown();
    /** 
     * @brief �����Ƿ�ı䵱ǰ����Ŀ¼�Լ��ر����õ��ļ�������
     * ������ǰ��������Ϊdeamon���������� 
     * 
     * @param changeDir
     * @param closeFile
     */
    void configureDaemon( bool changeDir , bool closeFile);
    /** 
     * @brief ���ݵ�ǰ�������еķ���������صĴ���
     * �����deamon�������������runDaemon,����runDaemon����run����
     * ����ǰ��������̨����
     * ����ǿ���̨�����ֱ�ӵ���run���� 
     * 
     * @param argc
     * @param argv[]
     * 
     * @return 
     */
    int start(int argc , char* argv[] );
    /** 
     * @brief ��ʱ����
     * 
     * @return 
     */
    virtual int  initialize(); 
private:
    bool _nohup;
    /** 
     * @brief �Ƿ����ػ����� 
     */
    bool _service;
    /** 
     * @brief �Ƿ�ı乤��Ŀ¼
     */
    bool _changeDir;
    /** 
     * @brief �Ƿ�ر�û�õ��ļ�
     */
    bool _closeFiles;
    /** 
     * @brief �Ƿ�ر�
     */
    bool _destroyed;
    /** 
     * @brief �Ƿ����������stop����
     */
    bool _chlidStop;
    //std::string _name;
    /** 
     * @brief ����pid�ļ�
     */
    std::string _pidFile;
    /** 
     * @brief ���������ļ�·��
     */
    std::string _configFile;
    /** 
     * @brief ��ǰ�����е�����(stop|start)
     */
    std::string _cmd;
    std::string _chstdOut;
    std::string _chstdErr;
    std::string _noinit;
    tbutil::Monitor<tbutil::Mutex> _monitor;
    static Service* _instance;
};//end Servcie
}//end namespace tbutil
#endif
