#ifndef _CCONSTANT_H_
#define _CCONSTANT_H_


//日志级别枚举
class EnumLogLevel
{
public:
  static const int LogLevelAll = 0; //所有信息都写日志
  static const int LogLevelMid = 1;  //写错误、警告信息
  static const int LogLevelNormal = 2;  //只写错误信息
  static const int LogLevelStop = 3;  //不写日志
};

const int SMALL_BUF = 64;
const int MIDDLE_BUF = 400;
const int MAX_BUF = 1024;

const int MAX_FDS = 500;
const int MAX_EVENTS = 500;
const int USER_NUM = 10;

//日志级别的提示信息
static const char* KEYINFOPREFIX = " Key: \n";
static const char* ERRORPREFIX = " Error: \n";
static const char* WARNINGPREFIX = " Warning: \n";
static const char* INFOPREFIX  = " Info: \n";
  
static const int MAX_STR_LEN = 1024;

const int XMLDataError = 1001;
const int LoadXMLFileError = 1002;
const int ServerNameNotExists = 1003;
const int SoHandleError = 1004;
const int CallSoError = 1005;

#endif
