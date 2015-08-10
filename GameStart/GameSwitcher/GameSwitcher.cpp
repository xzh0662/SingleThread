/*
 * GameSwitcher.cpp
 *
 *  Created on: Jan 10, 2015
 *      Author: root
 */

#include <string>

#include "GameSwitcher.h"

//#include "GateMonitor.h"

GameSwitcher::GameSwitcher(void)
	: index_(-1)
{
}

GameSwitcher::~GameSwitcher(void)
{

}

GameSwitcher* GameSwitcher::instance_ = 0;

GameSwitcher* GameSwitcher::instance(void)
{
    if (instance_ == 0)
    {
        instance_ = new GameSwitcher();
    }
    return instance_;
}

void GameSwitcher::destroy(void)
{
    if (instance_ != 0)
    {
        delete instance_;
        instance_ = 0;
    }
}

int GameSwitcher::start(int index)
{
	printf("GameSwitcher::start index = %d\n", index);

	this->index_ = index;

	this->registeSignal(SIGINT);

	if (this->index_ < 0)
	{
		this->runAll();
	}
	else
	{
		this->runWithName();
	}

	return this->startSignalLoop();
}

int GameSwitcher::switcherIndex(void)
{
	return this->index_;
}

int GameSwitcher::signalCallBack(int sig)
{
	printf("GameSwitcher::signalCallBack sig=%d\n", sig);

	if (this->index_ < 0)
	{
		this->endAll();
	}
	else
	{
		this->endWithName();
	}

	return SignalEventBaseThread::signalCallBack(sig);;

}

int GameSwitcher::runAll(void)
{
	this->runGate();
	this->runScene();

	return 0;
}

int GameSwitcher::endAll(void)
{
	this->endGate();
	this->endScene();

	return 0;
}

int GameSwitcher::runWithName(void)
{
	std::string server_name;
	if (this->index_ == PROCESS_GAME_GATE)
	{// 这里从配置表获得
		server_name = "gate";
	}

	if (server_name == "gate")
	{
		return this->runGate();
	}
	else if (server_name == "scene")
	{
		return this->runScene();
	}

	return 0;
}

int GameSwitcher::endWithName(void)
{
	std::string server_name;
	if (this->index_ == PROCESS_GAME_GATE)
	{// 这里从配置表获得
		server_name = "gate";
	}

	if (server_name == "gate")
	{
		return this->endGate();
	}
	else if (server_name == "scene")
	{
		return this->endScene();
	}
	return 0;
}

int GameSwitcher::runGate(void)
{
//	GATE_MONITOR->eventBase(this->eventBase());
//	GATE_MONITOR->init();
//	GATE_MONITOR->start();

	printf("GameSwitcher::runGate\n");
	return 0;
}

int GameSwitcher::runScene(void)
{
	return 0;
}

int GameSwitcher::endGate(void)
{
//	GATE_MONITOR->stop();
//	GATE_MONITOR->final();

	printf("GameSwitcher::endGate\n");
	return 0;
}

int GameSwitcher::endScene(void)
{
	return 0;
}

