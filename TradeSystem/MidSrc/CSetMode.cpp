#include "CSetMode.h"
#include "CDefHeader.h"

int CSetMode::setnonblocking(int fd)
{
  int old_opt = fcntl(fd, F_GETFL);
  int new_opt = old_opt | O_NONBLOCK;
  fcntl(fd, F_SETFL, new_opt);
  return old_opt;
}

int CSetMode::set_epoll_mode(int epoll_fd, int sock_fd, int type)
{
  int ret = -1;
  struct epoll_event ev;
  ev.data.fd = sock_fd;
  switch(type)
  {
    case 1:
      ev.events = EPOLLIN | EPOLLET;
      ret = epoll_ctl(epoll_fd, EPOLL_CTL_ADD, sock_fd, &ev);
      setnonblocking(sock_fd);
    break;
    case 2:
      ev.events = EPOLLOUT | EPOLLET;
      ret = epoll_ctl(epoll_fd, EPOLL_CTL_MOD, sock_fd, &ev);
    break;
    case 3:
      ret = epoll_ctl(epoll_fd, EPOLL_CTL_DEL, sock_fd, &ev);
      close(sock_fd);
    break;
    default:
    break;
  }
  return ret;
}

