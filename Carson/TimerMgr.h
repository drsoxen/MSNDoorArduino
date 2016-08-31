#ifndef TIMER_Mgr
#define TIMER_Mgr

#include <ESP8266WiFi.h>
#include <vector>
#include "Timer.h"

class TimerMgr
{
public:
	TimerMgr();

  void createTimer(int milliseconds, std::function<void(void)> fn);
  void tickTimers();

private:
  std::vector<Timer*> m_timers;
  
};

#endif
