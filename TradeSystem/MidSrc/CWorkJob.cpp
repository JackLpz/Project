#include "CWorkJob.h"

CWorkJob::CWorkJob()
{
  client_fd = -1;
}


CWorkJob::~CWorkJob()
{

}

void CWorkJob::init(int fd)
{
  client_fd = fd;
}

int CWorkJob::receive_data()
{
   memset(buf, '\0', MAX_BUF);
   int len = recv(client_fd, buf, MAX_BUF, 0);
   if (len > 0)
   {
     cout<<"receive data is:"<<buf<<endl;
   }
   else 
   {
     if (len < 0)
       cout<<"receive data error"<<endl;
     return -1;
   }
   return len;
}

int CWorkJob::send_data(char* buf, int sizeBuf)
{
  if ( client_fd < 0  || !buf || sizeBuf <= 0 )
  	return -1;
  int iCurrSend = 0, offset = 0;
  while ( sizeBuf > 0 )
  {
    iCurrSend = send(client_fd, (char *)buf+offset, sizeBuf, 0);
    if ( iCurrSend <= 0 )
      break;
    sizeBuf -= iCurrSend;
    offset += iCurrSend;
  } 
  return offset;
}

void CWorkJob::run()
{
  int iRet = 0;
  int iRetCountSize = 0;
  char pRetInfo[10240];
  memset(pRetInfo, 0x00, sizeof(pRetInfo));
  iRetCountSize = receive_data();
  if(iRetCountSize == 0)
    return ;
  /*进行应用程序的调用*/
  if(strlen(buf) > 0)
  {
    ptCallBackServer = new CCallBackServer(buf);
    iRet = ptCallBackServer->getBackServerSoFromXML();
    iRet = ptCallBackServer->callBackServer(pRetInfo);
    iRet = this->send_data(pRetInfo, strlen(pRetInfo));
    delete ptCallBackServer;
  }
  return ;
}

void CWorkJob::close_conn(int epoll_fd, int& socket_fd)
{
  if(socket_fd > 0)
  {
    CSetMode::set_epoll_mode(epoll_fd, socket_fd, 3);
    socket_fd = -1;
  }
}
