#include "LockMgr.h"

int g_lockPin;
bool activeHigh = false;
LockMgr::LockMgr(int lockPin, TimerMgr* timerMgr)
{
  m_lockPin = lockPin;
  g_lockPin = m_lockPin;
  m_timer = timerMgr;
  pinMode(m_lockPin, OUTPUT);
  
  if(activeHigh)
    digitalWrite(m_lockPin, LOW);
  else
    digitalWrite(m_lockPin, HIGH);
}

void lock()
{
  if(activeHigh)
    digitalWrite(g_lockPin, HIGH);
  else
    digitalWrite(g_lockPin, LOW);
}

void unlock()
{
    if(activeHigh)
    digitalWrite(g_lockPin, LOW);
  else
    digitalWrite(g_lockPin, HIGH);
}

void LockMgr::changeLockState(LockStates state)
{
  switch(state)
  {
    case LOCK:
      lock();
    break;

    case UNLOCK:
      unlock();
    break;

    case PULSE_UNLOCK:
      unlock();
      m_timer->createTimer(1000,lock);
    break;

    case LONG_PULSE_UNLOCK:
      unlock();
      m_timer->createTimer(10000,lock);
    break;
  }
}
