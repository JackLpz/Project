CC=g++

.SUFFIXES:.cpp
 
.cpp.o:
	$(CC) -c $*.cpp

OBJ=CCondition.o CMutex.o CSemaphore.o CSetMode.o CWorkJob.o CLog.o\
	CEpollManager.o CServerSock.o CThreadPool.o Main.o CCallBackServer.o\
	tinystr.o tinyxmlerror.o tinyxmlparser.o tinyxml.o

TestServer:$(OBJ)
	$(CC)   $(OBJ) -o server -lpthread -ldl
clean:
	rm *.o
	rm *.lis

