#include "Timer.h"

Timer::Timer(int milliseconds, std::function<void(void)> fn)
{
  m_interval = milliseconds;
  m_callback = fn;
  m_startMillis = millis();
}

bool Timer::tick(unsigned long currentMillis)
{
  if (currentMillis - m_startMillis >= m_interval) 
  {
      m_callback();
      return true;
  }
  return false;
}
