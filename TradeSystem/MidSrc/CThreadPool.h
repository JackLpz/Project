#ifndef _CTHREAD_H_
#define _CTHREAD_H_
#include <exception>
#include <list>
#include <pthread.h>
#include "CMutex.h"
#include "CSemaphore.h"
#include "CWorkJob.h"
#include "CLog.h"

class CThreadPool
{
private:
  int m_thread_num;
  int m_max_request;
  pthread_t* m_threads;
  bool m_stop;
  CMutex m_mutex_locker;
  CSemaphore m_queue_locker;
  std::list<CWorkJob*> m_work_queue;
	Logger log;
public:
  CThreadPool(int thread_num=8, int max_requests=1000);
  ~CThreadPool();
  bool append_to_pool(CWorkJob* request);
	
private:
  void run();
  static void* worker(void* args);
};
#endif
