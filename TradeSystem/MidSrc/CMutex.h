#ifndef _CMUTEX_H_
#define _CMUTEX_H_

#include <exception>
#include <pthread.h>
#include <semaphore.h>

class CMutex
{
private:
  pthread_mutex_t m_mutex;
public:
  CMutex();
  ~CMutex();
  bool lock();
  bool unlock();
};
#endif

