/*
 * main.cpp
 *
 *  Created on: Jan 7, 2015
 *      Author: root
 */



#include "GlobalInfo.h"
#include "GameDeamon.h"
#include "GameSwitcher.h"
#include "stdlib.h"
#include "LogClient.h"


int main(int argc, char **argv)
{
	//GlobalInfo::useThreads();

	GlobalInfo::print();

	printf("argc = %d\n", argc);
	if (argc >= 1)
	{
		printf("argv0 = %s\n", argv[0]);
	}
	if (argc >= 2)
	{
		printf("argv1 = %s\n", argv[1]);
	}
	if (argc >= 3)
	{
		printf("argv2 = %s\n", argv[2]);
	}

	if (argc <= 1)
	{
		GAME_DEAMON->start();
	}
	else
	{
		GAME_SWITCHER->start(atoi(argv[1]));
	}
//	LOG_DEBUG << "test debug " << 0.6 << " " << 1 << ":" << 'a';
//	LOG_INFO << "test info";
//	LOG_WARN << "test WARN";
//	LOG_ERROR << "test debug";
//	LOG_FATAL << "test fatal";

	return 0;
}
