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
Channel::Channel() {
    _prev = NULL;
    _next = NULL;
    _expireTime = 0;
}

/*
 * ����
 *
 * @param   chid    ChannelId
 */
void Channel::setId(uint32_t id) {
    _id = id;
}

/*
 * �õ�ID
 */
uint32_t Channel::getId() {
    return _id;
}

void Channel::setArgs(void *args) {
    _args = args;
}

void *Channel::getArgs() {
    return _args;
}

void Channel::setHandler(IPacketHandler *handler) {
    _handler = handler;
}

IPacketHandler *Channel::getHandler() {
    return _handler;
}

/*
 * ���ù���ʱ��
 *
 * @param milliseconds ������, 0Ϊ��������
 */
void Channel::setExpireTime(int64_t expireTime) {
    _expireTime = expireTime;
}
}
