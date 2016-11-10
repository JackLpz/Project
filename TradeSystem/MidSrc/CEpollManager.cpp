#include "CEpollManager.h"
#include "CServerSock.h"
#include "CSetMode.h"
#include <iostream>
using namespace std;

CEpollManager::CEpollManager(CServerSock *serv_socket)
{
  serv_sock = serv_socket;
  epoll_fd = epoll_create(MAX_FDS);
  listen_fd = serv_sock->get_listen_socket();
  CSetMode::set_epoll_mode(epoll_fd, listen_fd, 1);
  pool = new CThreadPool();
  work_list = new CWorkJob[USER_NUM];
}

CEpollManager::~CEpollManager()
{
  delete []work_list;
  delete pool;
}

int CEpollManager::get_epoll_fd()
{
  return epoll_fd;
}

void CEpollManager::run_epoll_event()
{
  int num = epoll_wait(epoll_fd, events, MAX_FDS, -1 );
  char buf[100] = {'\0'};
  for(int i=0; i<num; ++i)
  {
    int getsock = events[i].data.fd;
    if(getsock == listen_fd)
    {
      struct sockaddr_in client_addr;
      socklen_t len = sizeof(struct sockaddr);
      int connfd = accept(listen_fd,(struct sockaddr*)&client_addr, &len);
      CSetMode::set_epoll_mode(epoll_fd, connfd, 1);
      cout<<"there is a connect,connfd is "<<connfd<<endl;
      work_list[connfd - USER_NUM].init(connfd);
    }
    else if(events[i].events & EPOLLIN)
    {
      pool->append_to_pool(&work_list[getsock - USER_NUM]);
    }
    
    else if(events[i].events & ( EPOLLHUP | EPOLLERR))
    {
      work_list[getsock - USER_NUM].close_conn(epoll_fd, getsock);
    }
  }
}

