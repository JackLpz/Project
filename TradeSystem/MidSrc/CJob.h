#ifndef _CJOB_H_
#define _CJOB_H_

class CJob
{
public:
  CJob(){}
  virtual ~CJob(){}
  virtual int receive_data() = 0;
  virtual int send_data(char* buf, int sizeBuf) = 0;
};
#endif

