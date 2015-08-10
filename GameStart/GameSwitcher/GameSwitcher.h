/*
 * GameSwitcher.h
 *
 *  Created on: Jan 10, 2015
 *      Author: root
 */

#ifndef GAMESTART_GAMESWITCHER_GAMESWITCHER_H_
#define GAMESTART_GAMESWITCHER_GAMESWITCHER_H_

#include "Thread.h"
#include <map>

#define SIGHUP  			1
#define SIGINT  			2
#define SIGQUIT 			3
#define SIGILL  			4
#define SIGTRAP 			5
#define SIGABRT 			6
#define SIGBUS  			7
#define SIGFPE  			8
#define SIGKILL 			9
#define SIGUSR1 			10
#define SIGSEGV 			11
#define SIGUSR2 			12
#define SIGPIPE 			13
#define SIGALRM 			14
#define SIGTERM 			15
#define SIGCHLD 			17
#define SIGCONT 			18
#define SIGSTOP 			19
#define SIGTSTP 			20
#define SIGTTIN 			21
#define SIGTTOU 			22
#define SIGURG  			23
#define SIGXCPU 			24
#define SIGXFSZ 			25
#define SIGVTALRM   		26
#define SIGPROF 			27
#define SIGWINCH			28
#define SIGIO   			29
#define SIGPWR  			30
#define SIGSYS  			31

#define SIGNAL_OFFSET   	20
#define SIGNAL_MAXVAL   	32

// Signal to turn server on
#define SIGNAL_SVC_ON   	SIGNAL_OFFSET + 1
// Signal to turn server off
#define SIGNAL_SVC_OFF  	SIGNAL_OFFSET + 2
// Signal to quit server
#define SIGNAL_QUIT 		SIGNAL_OFFSET + 3
// Signal to turn logger on
#define SIGNAL_LOG_ON   	SIGNAL_OFFSET + 4
// Signal to turn logger off
#define SIGNAL_LOG_OFF  	SIGNAL_OFFSET + 5


#define PROCESS_GAME_GATE  1
#define PROCESS_GAME_SCENE 2

class GameSwitcher : public SignalEventBaseThread
{
private:
	GameSwitcher(void);
	virtual ~GameSwitcher(void);

public:
	static GameSwitcher* instance(void);
	static void destroy(void);

	int start(int index);

	int switcherIndex(void);

private:
	virtual int signalCallBack(int sig);

	int runAll(void);
	int endAll(void);

	int runWithName(void);
	int endWithName(void);

	int runGate(void);
	int runScene(void);

	int endGate(void);
	int endScene(void);

private:
	static GameSwitcher* instance_;

	int index_;
};

#define GAME_SWITCHER GameSwitcher::instance()


#endif /* GAMESTART_GAMESWITCHER_GAMESWITCHER_H_ */
