#ifndef _CSERVERSOCK_H_
#define _CSERVERSOCK_H_

#include "CDefHeader.h"
#include "CLog.h"

class CServerSock
{
public:
  CServerSock(){}
  CServerSock(int port_num,  char *ip_addr):port(port_num),ip(ip_addr){ init_listen_socket();}
  ~CServerSock();
  int get_listen_socket() const;

private:
  int create_socket();
  int bind_addr();
  int listen_socket();
  int init_listen_socket();
private:
  int port;
  char *ip;
  int socket_fd;
  Logger log;
  const static int max_list = 5;
  struct sockaddr_in server_addr;
  struct sockaddr_in client_addr;
};
#endif

