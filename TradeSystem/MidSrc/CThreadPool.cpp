#include "CThreadPool.h"
#include "CDefHeader.h"
#include "CWorkJob.h"
#include "CJob.h"

CThreadPool::CThreadPool(int thread_num, int max_request):m_thread_num(thread_num),
				m_max_request(max_request),m_stop(false),m_threads(NULL)
{
  if(thread_num<=0 || max_request<=0)
  	throw std::exception();
  m_threads = new pthread_t[m_thread_num];
  if(!m_threads)
    throw std::exception();
  
  for(int i=0; i<m_thread_num; ++i)
  {
    log.TraceInfo("create %d thread start", i+1);
    if(pthread_create(m_threads+i, NULL, worker, this) != 0)
    {
    	delete []m_threads;
    	throw std::exception();
    }
    if(pthread_detach(m_threads[i]))
    {
    	delete []m_threads;
    	throw std::exception();
    }
  }
}

CThreadPool::~CThreadPool()
{
  log.TraceInfo("delete all thread start");
  if(m_threads)
  {
    delete []m_threads;
    m_stop = true;
  }
}

bool CThreadPool::append_to_pool(CWorkJob* request)
{
  m_mutex_locker.lock();
  if(m_work_queue.size() > m_max_request)
  {
    m_mutex_locker.unlock();
    return false;
  }
  m_work_queue.push_back(request);
  m_mutex_locker.unlock();
  m_queue_locker.post();
  return true;
}

void* CThreadPool::worker(void* args)
{
  CThreadPool* pool = (CThreadPool*)args;
  pool->run();
  return pool;
}

void CThreadPool::run()
{
  while(!m_stop)
  {
    m_queue_locker.wait();
    m_mutex_locker.lock();
    if(m_work_queue.empty())
    {
    	m_mutex_locker.unlock();
    	continue;
    }
    CWorkJob* request = m_work_queue.front();
    m_work_queue.pop_front();
    m_mutex_locker.unlock();
    if(!request)
    	continue;
    log.TraceInfo("start to run request...");
    request->run();
  }
}
