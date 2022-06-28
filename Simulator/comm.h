#ifndef COMMN_H
#define COMMN_H

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <errno.h>
#include <poll.h>
#include <iostream>
#include <thread>
#include <unistd.h>
#include <string.h>
#include <algorithm>
#include <stdlib.h>
#include <netdb.h>
#include <poll.h>
#include <vector>
#include <mutex>
using namespace std;
#define MaxBufSize 1024
///////udcdata-->payload-->Msg//////////////////
#define CTRL_MSGE 0x81 //121
#define TERM_MSGE 0x82
#define DATA_MSGE 0x83
#define PORTNUMBER 1500
typedef struct
{
    uint32_t ctrlMsge;
    char   buffer[512];
    uint16_t size;
}Msg;
/************************************************/
#define COMMAND 0X01
#define REQUEST 0x04
#define RESPONE 0X14
#define TRIGGERRESPONSE 0X16
#define TRIGGERREQUEST 0x06

#define STATICREQ 0X51 //81
#define STATICRESP 0X52
#define JOBREQ 0X53
#define JOBRESPONSE 0X54
#define UPLOADMSGE 0X55
#define LOG 0X56
typedef struct
{
    uint32_t MsgType;
    char   buffer[256];
    uint16_t size;
}Payload;
/***************************************************/

class ComInterface{
  std::vector<std::string> dataHoldertoSend;
  std::vector<Payload> UDCpayload;
  void CmndDataFomate(Msg*);
  public:
  Msg ctrlmsge = {TERM_MSGE,"ABC",3};
  Msg datamsge = {DATA_MSGE,"XXX",3};
  bool msgeType = false;
  Msg msgrxv;
  struct pollfd pfds[1];
    int client;
    int portNum = PORTNUMBER; 
    bool isExit = false;
    int bufsize = MaxBufSize;
    char buffer[MaxBufSize];
    std::thread commThread;
    void ConnectServer();
    void threadAction();
    void startThread();
    void closeConnection();     
    void SendUDCData(Payload&);
    bool ignStatus = false;    
    protected:
    virtual void receivecb(Payload&) {        
    }
};

#endif
