/*
 * GameDeamon.cpp
 *
 *  Created on: Jan 9, 2015
 *      Author: root
 */

#include "GameDeamon.h"
#include "GameSwitcher.h"

#include<sys/types.h>
#include<sys/wait.h>
#include <unistd.h>
#include <stdlib.h>

GameDeamon::GameDeamon(void) :
		closing_(0)
{
}

GameDeamon::~GameDeamon(void)
{

}

GameDeamon* GameDeamon::instance_ = 0;

GameDeamon* GameDeamon::instance(void)
{
    if (instance_ == 0)
    {
        instance_ = new GameDeamon();
    }
    return instance_;
}

void GameDeamon::destroy(void)
{
    if (instance_ != 0)
    {
        delete instance_;
        instance_ = 0;
    }
}

int GameDeamon::start(void)
{
	this->registeSignal(SIGINT);

	SignalEventBaseThread::start();

	this->activeAllServer();

	return this->stop();
}

int GameDeamon::signalCallBack(int sig)
{
	SignalEventBaseThread::signalCallBack(sig);

	printf("GameDeamon::signalCallBack sig=%d\n", sig);

	this->closing_ = true;

	for (std::map<pid_t, int>::const_iterator iter = this->pid_map_.begin();//
			iter != this->pid_map_.end(); ++iter)
	{
		printf("kill pid = %d\n", iter->first);
		kill(iter->first, SIGINT);
	}

	return 0;
}

int GameDeamon::stop(void)
{
	return this->waitEx();
}

int GameDeamon::activeAllServer(void)
{
	this->activeServer(PROCESS_GAME_GATE);
	//this->activeServer(PROCESS_GAME_GATE);
	return 0;
}

int GameDeamon::activeServer(int type)
{
	pid_t pid = fork();
	if (pid < 0)
	{
		printf("GameDeamon::start fork error\n");
		exit(0);
	}
	else if (pid == 0)
	{
		this->spawn(type);
	}
	else
	{
		this->pid_map_[pid] = type;

		printf("GameDeamon::start fork pid=%d\n", pid);
	}

	return 0;
}

int GameDeamon::spawn(int type)
{
	//int index = 1;
	if (type == PROCESS_GAME_GATE)
	{
		char *argv[] = {(char *)"GameServer gate", (char *)"1", (char *)0};

		execv("./GameServer", argv);
	}
	return 0;
}

int GameDeamon::waitEx(void)
{
	while (!this->closing_ || !this->pid_map_.empty())
	{
		int log;
		pid_t pid = ::wait(&log);

		printf("GameDeamon::waitEx pid = %d log = %d\n", pid, log);
		int type = this->pid_map_[pid];
		this->pid_map_.erase(pid);

		//主进程就应该对子进程负责，暂时没想到其他的
		if (!this->closing_)
		{
			this->activeServer(type);
		}
	}

	return 0;
}

