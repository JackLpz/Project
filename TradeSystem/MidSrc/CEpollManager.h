#ifndef _CEPOLLMANAGER_H_
#define _CEPOLLMANAGER_H_

#include "CDefHeader.h"
#include "CServerSock.h"
#include "CThreadPool.h"
#include "CWorkJob.h"
#include "CLog.h"

class CEpollManager
{
private:
  struct epoll_event events[MAX_EVENTS];
  int epoll_fd;
  int listen_fd;
  CServerSock *serv_sock;
  CWorkJob *work_list;
  CThreadPool *pool;
  Logger log;
public:
  CEpollManager(){}
  CEpollManager(CServerSock *serv_socket);
  ~CEpollManager();
  int get_epoll_fd();
  void run_epoll_event();
};
#endif

