#include "CServerSock.h"

int CServerSock::get_listen_socket() const
{
  return socket_fd;
}

CServerSock::~CServerSock()
{
  close(socket_fd);
}

int CServerSock::create_socket()
{
  log.TraceInfo("create socket start....");
  socket_fd = socket(PF_INET, SOCK_STREAM, 0);
  assert(socket_fd >= 0);
  int opt = 0;
  setsockopt(socket_fd, SOL_SOCKET, SO_REUSEADDR, (const void*)&opt, sizeof(opt));
  return 1;
}

int CServerSock::bind_addr()
{
  log.TraceInfo("bind socket start,ip = [%s],port = [%d]",ip, port);
  bzero(&server_addr, sizeof(server_addr));
  server_addr.sin_family = AF_INET;
  server_addr.sin_port = htons(port);
  inet_pton(AF_INET, ip, &server_addr.sin_addr);
  if(bind(socket_fd,(sockaddr*)&server_addr, sizeof(server_addr)) != -1)
    return 1;
  return -1;
}

int CServerSock::listen_socket()
{
  log.TraceInfo("listen socket start");
  if(listen(socket_fd, max_list) != -1)
    return 1;
  return -1;
}



int CServerSock::init_listen_socket()
{
  create_socket();
  bind_addr();
  listen_socket();
}

