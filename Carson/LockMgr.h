#ifndef LOCK_MGR
#define LOCK_MGR

#include <ESP8266WiFi.h>
#include "TimerMgr.h"

enum LockStates {LOCK = 0, UNLOCK, PULSE_UNLOCK, LONG_PULSE_UNLOCK};

class LockMgr
{
public:
	LockMgr(int lockPin, TimerMgr* timerMgr);
	void changeLockState(LockStates state);

  int m_lockPin;

private:
//void lock();
//void unlock();

TimerMgr* m_timer;
 
};

#endif
