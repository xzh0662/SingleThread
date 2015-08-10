/*
 * EventMonitor.h
 *
 *  Created on: Aug 10, 2015
 *      Author: root
 */

#ifndef EVENTMONITOR_H_
#define EVENTMONITOR_H_

class EventMonitor
{
public:
	EventMonitor(event_base* base);
	virtual ~EventMonitor(void);

	void handleRead(int fd, Buffer *buffer);
	virtual int send(int fd, Buffer *buffer);
	virtual int receive(int fd, Buffer *buffer) =0;
	virtual void handleClosed(int fd) = 0;
	virtual void handleConnected(void){};

	virtual int receiveHandleMessage(Buffer *buffer);
	virtual int sendHandleMessage(Buffer *buffer);

	event_base* eventBase(void);

protected:
	virtual int sendMessage(int fd, Buffer *buffer) = 0;

private:

	static int receiveHandleMessage(void *self, void *msg);
	static int sendHandleMessage(void *self, void *msg);

	event_base* event_base_;
};



#endif /* EVENTMONITOR_H_ */
