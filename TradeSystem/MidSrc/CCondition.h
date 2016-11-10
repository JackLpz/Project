#ifndef _CCONDITION_H_
#define _CCONDITION_H_

#include <exception>
#include <pthread.h>
#include <semaphore.h>

class CCondition
{
private:
  pthread_mutex_t m_mutex;
  pthread_cond_t m_cond;
  
public:
  CCondition();
  ~CCondition();
  bool wait();
  bool signal();
};
#endif
