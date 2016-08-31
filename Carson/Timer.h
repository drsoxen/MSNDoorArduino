#ifndef TIMER
#define TIMER

#include <ESP8266WiFi.h>

class Timer
{
public:
	Timer(int milliseconds, std::function<void(void)> fn);
  bool tick(unsigned long currentMillis);
  
private:
  std::function<void(void)> m_callback;
  unsigned long m_startMillis;

  long m_interval;
};

#endif
