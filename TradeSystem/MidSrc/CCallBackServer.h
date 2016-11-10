#ifndef _CBACK_SERVER_H_
#define _CBACK_SERVER_H_

#include "CDefHeader.h"
#include "tinyxml.h"
#include "tinystr.h"

/*依据前台传进的报文 进行解析*/
class CCallBackServer
{
private:
  string strXMLInfo;
  string strPath;
  string strSoPath;
  string localXMLFile;
  string strServerNameFunc;
public:
  CCallBackServer()
  {
    this->strXMLInfo = "";
    this->strPath = "";
    this->strSoPath = "/home/project/backSo/";
    this->localXMLFile = "/home/project/property/backServerInfo.xml";
    this->strServerNameFunc = "";
  }
  CCallBackServer(string strXMLInfo)
  {
    this->strXMLInfo = strXMLInfo;
    this->localXMLFile = "/home/project/property/backServerInfo.xml";
    this->strSoPath = "/home/project/backSo/";
    this->strServerNameFunc = "";
    cout<<"XML Info = "<<this->strXMLInfo<<endl;
    cout<<"XML File Info = "<<this->localXMLFile<<endl;
    cout<<"So path = "<<this->strSoPath<<endl;
  }
  ~CCallBackServer(){}
  
  int getBackServerSoFromXML();
  int callBackServer(char* pRetInfo);
};
#endif