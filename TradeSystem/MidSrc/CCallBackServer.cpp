#include "CCallBackServer.h"

/*用于读取配置文件 进行so名称的获取*/
int CCallBackServer::getBackServerSoFromXML()
{
  //cout<<"XML info = "<<this->strXMLInfo<<endl;
  if(this->strXMLInfo == "")
  	return XMLDataError;
  bool bServerExit = false;
  /*首先进行前台XML的解析*/
  TiXmlDocument *doc = new TiXmlDocument();
  doc->Parse(this->strXMLInfo.c_str(), 0,TIXML_ENCODING_UNKNOWN); 
  TiXmlElement* root = doc->RootElement();
  /*报文格式详见报文设计文档*/
  TiXmlNode*  serverNode = root->FirstChild( "ServerName" );
  const char* serverName = serverNode->ToElement()->GetText();
  this->strServerNameFunc = serverName;
  //cout<<"serverName is : "<<serverName<<endl;
  root = NULL;

  /*读取本地的.so配置文件 进行so的获取  该服务到底调用哪个.so*/
  //cout<<"XML File Info = "<<this->localXMLFile<<endl;
  TiXmlDocument localDoc(this->localXMLFile.c_str());  
  bool loadOkay = localDoc.LoadFile();  
  if (!loadOkay)
  {      
    cout<<"Could not load local xml file."<<endl; 
    if(doc != NULL) delete doc;
    return LoadXMLFileError;
  }
  root = localDoc.RootElement();
  for( TiXmlNode*  item = root->FirstChild( "item" );  item;  item = item->NextSibling( "item" ) ) 
  {
  	TiXmlNode* localchild = item->FirstChild();  
    const char* localServerName = localchild->ToElement()->GetText();  
    if (localServerName) 
    {  
      cout<<"localServerName: "<<localServerName<<endl;
    } 
    else 
    {  
      cout<<"localServerName:"<<endl;
    }
    localchild = item->IterateChildren(localchild);
    const char* localSoName = localchild->ToElement()->GetText();
    if(localSoName)
    {
      cout<<"localSoName: "<<localSoName<<endl;
    }
    else 
    {
      cout<<"localSoName:"<<endl;
    }

    if(strcmp(localServerName, serverName) == 0)
    {
    	this->strSoPath += localSoName;
    	bServerExit = true;
    	cout<<"strSoPath = "<<this->strSoPath<<endl;
    	break;
    }
  }
  if(doc != NULL) delete doc;
  if(bServerExit == false)
  {
  	cout<<"server name noe exists in local xml file, please check,sername = "<<serverName<<endl;
  	return ServerNameNotExists;
  }
  return 0;
}

int CCallBackServer::callBackServer(char* pRetInfo)
{
  cout<<"XML Info = "<<this->strXMLInfo<<endl;
  cout<<"So path = "<<this->strSoPath<<endl;
  void* handle = NULL;
  handle = dlopen(this->strSoPath.c_str(),RTLD_LAZY);
  if(handle == NULL)
  {
    cout<<"handle error"<<dlerror()<<endl;
    return SoHandleError;
  }
  typedef int(*server)(const char*, char*);
  server s = NULL;
  s = (server)dlsym(handle, this->strServerNameFunc.c_str());
  if(s == NULL)
  {
    cout<<"server error: "<<dlerror()<<endl;
    dlclose(handle);
    return CallSoError;
  }
  (*s)(this->strXMLInfo.c_str(), pRetInfo);
  cout<<"pRetInfo = "<<pRetInfo<<endl;
  dlclose(handle);
  return 0;
}