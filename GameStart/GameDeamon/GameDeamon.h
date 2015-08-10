/*
 * GameDeamon.h
 *
 *  Created on: Jan 9, 2015
 *      Author: root
 */

#ifndef GAMESTART_GAMEDEAMON_GAMEDEAMON_H_
#define GAMESTART_GAMEDEAMON_GAMEDEAMON_H_

#include "Thread.h"
#include <map>

class GameDeamon : public SignalEventBaseThread
{
private:
	GameDeamon(void);
	virtual ~GameDeamon(void);

public:
	static GameDeamon* instance(void);
	static void destroy(void);

	int start(void);

private:
	virtual int signalCallBack(int sig);

	int stop(void);

	int activeAllServer(void);
	int activeServer(int type);
	int spawn(int type);
	int waitEx(void);

private:
	static GameDeamon* instance_;

	std::map<pid_t, int> pid_map_;
	bool closing_;
};

#define GAME_DEAMON GameDeamon::instance()

#endif /* GAMESTART_GAMEDEAMON_GAMEDEAMON_H_ */
