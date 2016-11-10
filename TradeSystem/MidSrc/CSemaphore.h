#ifndef _SEPAMHORE_H_
#define _SEPAMHORE_H_

#include <pthread.h>
#include <exception>
#include <semaphore.h>

class CSemaphore
{
private:
  sem_t m_sem;
public:
  CSemaphore();
  ~CSemaphore();
  bool wait();
  bool post();
};

#endif
