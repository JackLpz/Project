#include "CMutex.h"
CMutex::CMutex()
{
  if(pthread_mutex_init(&m_mutex, NULL) != 0)
  {
    throw std::exception();
  }
}
	
CMutex::~CMutex()
{
  pthread_mutex_destroy(&m_mutex);
}
	
bool CMutex::lock()
{
  return pthread_mutex_lock(&m_mutex) == 0;
}
	
bool CMutex::unlock()
{
  return pthread_mutex_unlock(&m_mutex) == 0;
}

