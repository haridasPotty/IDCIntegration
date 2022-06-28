#include "commn.h"

void Server::CmndDataFomate(Msg* mptr){
  Payload payload;
  QString testData =vectCommand.back();
  vectCommand.pop_back();
  qDebug() << testData;
  payload.MsgType = COMMAND;
  memcpy(payload.buffer,testData.toStdString().c_str(),testData.size() );
  payload.size = testData.size();
  mptr->size = payload.size;
  memcpy( mptr->buffer,&payload,sizeof(payload) );
}
void Server::sendDatatoListWidget(char* ptr,uint16_t length){
    char d2[12];
    memcpy(d2,ptr,length);
    std::string tx = d2;
    QString tstr = QString::fromStdString(tx);    
    emit serverCustomSignals(tstr);
}

void Server::PayloadIdentification( Msg & msgrxv){
    Payload data;
    memcpy (&data,msgrxv.buffer,sizeof(data) );
    if (data.MsgType == LOG){
        qDebug() << "LOG msge detected";
        sendDatatoListWidget(data.buffer,data.size);
    }
    else if(data.MsgType == UPLOADMSGE){
        qDebug() << "UPLOADMSGE msge detected";
        sendDatatoListWidget(data.buffer,data.size);
    }
    else if(data.MsgType == TRIGGERREQUEST){
         qDebug() << "TRIGGERREQUEST msge detected";
         sendDatatoListWidget(data.buffer,data.size);
    }
    else if(data.MsgType == STATICREQ){
         qDebug() << "STATICREQ msge detected";
    }
    else{
        qDebug() << "Valid msge not rxved";
    }
}

Server::Server(){}

bool Server::connect(){
    serverHandler = socket(AF_INET, SOCK_STREAM, 0);
    if (serverHandler < 0) {
        qDebug() << "\nError establishing socket..." ;
        return false;
    }
     qDebug() << "\n=> Socket server has been created..." ;
     server_addr.sin_family = AF_INET;
     server_addr.sin_addr.s_addr = htons(INADDR_ANY);
     server_addr.sin_port = htons(portNum);

     if ((bind(serverHandler, (struct sockaddr*)&server_addr, \
                                  sizeof(server_addr))) < 0) {
            qDebug() << "=> Error binding connection, the socket \
                     has already been established..." ;
            return false;
        }

     size = sizeof(server_addr);
     qDebug() << "=> Looking for clients..." ;
     listen(serverHandler, 1);
     server = accept(serverHandler,\
                     (struct sockaddr*)&server_addr,&size);
     if (server < 0) {
            qDebug()<< "=> Error on accepting...";
            return false;
     }
     return true;
}



void Server::threadAction(){
    pfds[0].fd = server;
    pfds[0].events = POLLIN;
     Msg msgrxv;
    while(!isExit){
        sleep(1);
        memset(&msgrxv,'0',sizeof(msgrxv));
        memset(buffer,'0',MaxBufSize);
#if 1
        if (vectCommand.isEmpty()){
            msgrxv.ctrlMsge = CTRL_MSGE;
            memcpy( msgrxv.buffer,"CTRLMSGE",8);
            msgrxv.size = 8;
            memcpy(buffer,&msgrxv,sizeof(msgrxv) );
        }
        else{
            this->CmndDataFomate( &msgrxv );
            msgrxv.ctrlMsge = DATA_MSGE;
            memcpy(&buffer,&msgrxv,sizeof(msgrxv));
        }
#endif
#if TEST
        Payload udcPayload;
        udcPayload.MsgType = COMMAND;
        udcPayload.size = 6;
        memcpy(&udcPayload.buffer,"IGNACC",udcPayload.size);

        msgrxv.ctrlMsge = DATA_MSGE;
        msgrxv.size = udcPayload.size;
        memcpy(&msgrxv.buffer,&udcPayload,sizeof(udcPayload) );

        memcpy(buffer, &msgrxv, sizeof(msgrxv) );
#endif

        int ret = send(server, buffer, MaxBufSize, 0);
        if (ret != -1){
            //qDebug() <<"send to  UDC";
        }
        else{
            qDebug() <<"send failed";
        }

        memset(buffer,'0',MaxBufSize);
        memset(&msgrxv,'0',sizeof(msgrxv));
        int num_events = poll(pfds, 1, 100);
        if (num_events == 0) {
            printf("Poll timed out!\n");
        }
        else  {
            int pollin_happened = pfds[0].revents & POLLIN;
            if (pollin_happened) {               
                recv(server, buffer, MaxBufSize, 0);
                memcpy(&msgrxv,buffer,sizeof(msgrxv) );
                this->PayloadIdentification(msgrxv);
            }
            else  {
                printf("Unexpected event occurred: %d\n", pfds[0].revents);
            }
        }      
    }
}

void Server::startThread()
{
    commThread = std::thread( [this]() {this->threadAction();}  );
    commThread.detach();
}

void Server::stopConnection()
{
    isExit = true;
    close(server);
}
