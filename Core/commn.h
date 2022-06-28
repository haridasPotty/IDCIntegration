#ifndef COMMN_H
#define COMMN_H
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <poll.h>
#include <iostream>
#include <thread>
#include <unistd.h>
#include <QObject>
#include <string.h>
#include <algorithm>
#include <QVector>
#include <QString>
#include <QDebug>
using namespace std;
#define MaxBufSize 1024
#define PORTNUMBER 1500

#define CTRL_MSGE 0x81
#define TERM_MSGE 0x82
#define DATA_MSGE 0x83
typedef struct
{
    uint32_t ctrlMsge;
    char   buffer[512];
    uint16_t size;
}Msg;
#define COMMAND 0X01
#define REQUEST 0x04
#define RESPONE 0X14
#define TRIGGERRESPONSE 0X16
#define TRIGGERREQUEST 0x06
#define STATICREQ 0X51
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

class Server:public QObject
{
    Q_OBJECT

signals:
public:

    int  server,serverHandler;
    int portNum = PORTNUMBER;
    bool isExit = false;
    char buffer[MaxBufSize];
    struct sockaddr_in server_addr;
    socklen_t size;
    struct pollfd pfds[1];
    void CmndDataFomate(Msg*);
    void PayloadIdentification(Msg&);
    void sendDatatoListWidget(char* ptr,uint16_t length);
public:
    Server();
    bool connect();
    std::thread commThread;
    void threadAction();
    void startThread();
    void stopConnection();   
    QVector<QString> vectCommand;

signals:
    void serverCustomSignals(QString);

};

#endif // COMMN_H
