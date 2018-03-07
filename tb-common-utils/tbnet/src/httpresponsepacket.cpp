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

#include "tbnet.h"

namespace tbnet {

/*
 * ���캯��
 */
HttpResponsePacket::HttpResponsePacket() {
    _status = true;
    _body = NULL;
    _bodyLen = 0;
    _isKeepAlive = false;
    _statusMessage = NULL;
}

/*
 * ��������
 */
HttpResponsePacket::~HttpResponsePacket() {
    if (_body) {
        ::free(_body);
    }
    if (_statusMessage) {
        ::free(_statusMessage);
        _statusMessage = NULL;
    }
}

/*
 * ��װ
 */
bool HttpResponsePacket::encode(DataBuffer *output) {
    if (_statusMessage) {
        output->writeBytes(_statusMessage, strlen(_statusMessage));
        output->writeBytes("\r\n", 2);
    } else if (_status) { //HTTP/1.1 200 OK
        output->writeBytes(TBNET_HTTP_STATUS_OK, strlen(TBNET_HTTP_STATUS_OK));
    } else { // HTTP/1.1 404 Not Found
        output->writeBytes(TBNET_HTTP_STATUS_NOTFOUND, strlen(TBNET_HTTP_STATUS_NOTFOUND));
    }
    //�̶��ֶ�
    if (_isKeepAlive) {
        output->writeBytes(TBNET_HTTP_KEEP_ALIVE, strlen(TBNET_HTTP_KEEP_ALIVE));
    } else {
        output->writeBytes(TBNET_HTTP_CONN_CLOSE, strlen(TBNET_HTTP_CONN_CLOSE));
    }
    if (_headerMap.find("Content-Type") == _headerMap.end()) {
        output->writeBytes(TBNET_HTTP_CONTENT_TYPE, strlen(TBNET_HTTP_CONTENT_TYPE));
    }
    char tmp[64];
    int len = sprintf(tmp, TBNET_HTTP_CONTENT_LENGTH, _bodyLen);
    output->writeBytes(tmp, len);

    // �û��Զ��峤��
    for (STRING_MAP_ITER it=_headerMap.begin(); it!=_headerMap.end(); it++) {
        output->writeBytes(it->first.c_str(), strlen(it->first.c_str()));
        output->writeBytes(": ", 2);
        output->writeBytes(it->second.c_str(), strlen(it->second.c_str()));
        output->writeBytes("\r\n", 2);
    }

    // ����
    output->writeBytes("\r\n", 2);
    // bodyLen
    output->writeBytes(_body, _bodyLen);
    //assert(_packetHeader._dataLen == output->getDataLen());

    return true;
}

/*
 * �⿪
 */
bool HttpResponsePacket::decode(DataBuffer *input, PacketHeader *header) {
    return true;
}

/*
 * ����header
 */
void HttpResponsePacket::setHeader(const char *name, const char *value) {
    if (name[0] == 'C') {
        if (strcmp(name, "Connection") == 0 || strcmp(name, "Content-Length") == 0) {
            return;
        }
    }
    _headerMap[name] = value;
}

/*
 * ����״̬
 */
void HttpResponsePacket::setStatus(bool status, const char *statusMessage) {
    _status = status;
    if (_statusMessage) {
        ::free(_statusMessage);
        _statusMessage = NULL;
    }
    if (statusMessage) {
        _statusMessage = strdup(statusMessage);
    }
}

/*
 * ��������
 */
void HttpResponsePacket::setBody(const char *body, int len) {
    if (body) {
        _body = (char *) malloc(len);
        memcpy(_body, body, len);
        _bodyLen = len;
    }
}

/*
 * �Ƿ�keepalive
 */
void HttpResponsePacket::setKeepAlive(bool keepAlive) {
    _isKeepAlive = keepAlive;
}


}

