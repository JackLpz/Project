#ifndef _CWORKJOB_H_
#define _CWORKJOB_H_

#include "CJob.h"
#include "CDefHeader.h"
#include "CSetMode.h"
#include "CLog.h"
#include "CCallBackServer.h"

class CWorkJob : public CJob
{
public:
  CWorkJob();
  ~CWorkJob();
  void init(int fd);
  int receive_data();
  int send_data(char* buf, int sizeBuf);
  void run();
  void close_conn(int epoll_fd, int& sock_fd);
private:
  int client_fd;
  Logger log;
  CCallBackServer *ptCallBackServer;
  char buf[MAX_BUF];
};
#endif

