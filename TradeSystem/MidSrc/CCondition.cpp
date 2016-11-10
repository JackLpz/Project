#include "CCondition.h"

CCondition::CCondition()
{
  if(pthread_mutex_init(&m_mutex, NULL) != 0)
  {
    throw std::exception();
  }
  if(pthread_cond_init(&m_cond, NULL) != 0)
  {
    pthread_mutex_destroy(&m_mutex);
    throw std::exception();
  }
}

CCondition::~CCondition()
{
  pthread_mutex_destroy(&m_mutex);
  pthread_cond_destroy(&m_cond);
}

bool CCondition::wait()
{
  int ret = 0;
  pthread_mutex_lock(&m_mutex);
  ret = pthread_cond_wait(&m_cond, &m_mutex);
  pthread_mutex_unlock(&m_mutex);
  return ret == 0;
}

bool CCondition::signal()
{
  return pthread_cond_signal(&m_cond) == 0;
}

