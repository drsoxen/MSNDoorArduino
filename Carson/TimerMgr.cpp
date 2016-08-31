#include "TimerMgr.h"

TimerMgr::TimerMgr()
{

}

void TimerMgr::createTimer(int milliseconds, std::function<void(void)> fn)
{
  Timer *timer = new Timer(milliseconds, fn);
  m_timers.push_back(timer);
}

void TimerMgr::tickTimers()
{
  for (int i = 0; i < m_timers.size(); i++)
  {
    if(m_timers[i]->tick(millis()))
      {
        delete m_timers[i];
        m_timers.erase(m_timers.begin() + i);
        i--;
      }
  }
}

