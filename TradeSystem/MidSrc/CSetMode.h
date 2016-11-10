#ifndef _CSETMODE_H_
#define _CSETMODE_H_

class CSetMode
{
public:
  static int setnonblocking(int fd);
  static int set_epoll_mode(int epoll_fd, int sock_fd, int type);
};
#endif

