#include "CDefHeader.h"
#include "CServerSock.h"
#include "CEpollManager.h"

int main()
{
  char ip[] = "192.168.52.128";
  int port = 6000;
  CServerSock cs_sock(port, ip); //create socket, bind, listen, accept
  CEpollManager cpm(&cs_sock);  //for epoll

  while(true)
  {
  	cpm.run_epoll_event();
  }
  return 0;
}
