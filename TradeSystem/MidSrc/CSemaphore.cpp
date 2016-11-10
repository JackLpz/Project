#include "CSemaphore.h"
CSemaphore::CSemaphore()
{
  if(sem_init(&m_sem, 0, 0) != 0)
  {
    throw std::exception();
  }
}
	
CSemaphore::~CSemaphore()
{
  sem_destroy(&m_sem);
}
	
bool CSemaphore::wait()
{
  return sem_wait(&m_sem) == 0;
}
	
bool CSemaphore::post()
{
  return sem_post(&m_sem) == 0;
}

