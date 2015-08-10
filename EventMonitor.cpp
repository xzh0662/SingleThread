/*
 * EventMonitor.cpp
 *
 *  Created on: Aug 10, 2015
 *      Author: root
 */
#include "EventMonitor.h"

EventMonitor::EventMonitor(event_base* base)
	: event_base_(base)
{

}
EventMonitor::~EventMonitor(void)
{

}

void EventMonitor::handleRead(int fd, Buffer *buffer)
{
	this->receive(fd, buffer);
	delete buffer;
}

int EventMonitor::send(int fd, Buffer *buffer)
{
	this->sendHandleMessage(buffer);
	delete buffer;

	return 0;
}

int EventMonitor::receiveHandleMessage(Buffer *buffer)
{//这里做粘包,解密处理
	int fd = 0;
	*buffer >> fd;
	this->receive(fd, buffer);
	return 0;
}

int EventMonitor::sendHandleMessage(Buffer *buffer)
{//这里做加密处理
	int fd = 0;
	*buffer >> fd;

	this->sendMessage(fd, buffer);

	return 0;
}

event_base* EventMonitor::eventBase(void)
{
	return this->event_base_;
}

int EventMonitor::receiveHandleMessage(void *self, void *msg)
{
	EventMonitor* monitor = (EventMonitor*)self;
	return monitor->receiveHandleMessage((Buffer*)msg);
}

int EventMonitor::sendHandleMessage(void *self, void *msg)
{
	EventMonitor* monitor = (EventMonitor*)self;
	return monitor->sendHandleMessage((Buffer*)msg);
}
