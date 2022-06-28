#include "comm.h"


void ComInterface::ConnectServer(){
    client = socket(AF_INET, SOCK_STREAM, 0);
    if (client < 0)     {
    cout << "\nError establishing socket...\n" << endl;
    exit(1);
    }
    cout << " Socket client has been created..." << endl;
    struct sockaddr_in inet_server;
    memset(&inet_server, 0, sizeof(inet_server));
    inet_server.sin_family = AF_INET;
    inet_server.sin_addr.s_addr = inet_addr("127.0.0.1");
    inet_server.sin_port = htons(this->portNum);
    int rc = connect(client, (struct sockaddr *) &inet_server, 
    sizeof(inet_server));
}

void ComInterface::CmndDataFomate(Msg* mptr)
{
  Payload payload;
  memcpy(&payload,&UDCpayload.back(),sizeof(payload));
  UDCpayload.pop_back();
  for (int i=0;i<payload.size;++i){
      std::cout << payload.buffer[i];
  }
  std::cout << "\n";
  //payload.MsgType = REQUEST;
  //memcpy(payload.buffer,testData.c_str(),testData.size() );
  //payload.size = testData.size();
 // memcpy( mptr->buffer,&payload,sizeof(payload) );
}


void ComInterface::SendUDCData(Payload& data1)
{      
    UDCpayload.push_back(data1);  

}



void ComInterface::threadAction(){
    pfds[0].fd = client; 
    pfds[0].events = POLLIN; 
    Msg msgrxv;Msg ctrlBuff ;
     do {
        sleep(1);//to be removed after testing 
        memset(&ctrlBuff,'0',sizeof(ctrlBuff));            
        memset(buffer,'0',MaxBufSize);   
    	int num_events = poll(pfds, 1, 100); 
                if (num_events == 0) {
                    printf("Poll timed out!\n");
                 }
                else  {
                int pollin_happened = pfds[0].revents & POLLIN;
                    if (pollin_happened) {
                        //printf("File descriptor  is ready to read\n");
                        recv(client, buffer, bufsize, 0); 

                        memcpy(&msgrxv,buffer,sizeof(msgrxv));
                        if (msgrxv.ctrlMsge == DATA_MSGE){
                            Payload data;
                            memcpy(&data,msgrxv.buffer,sizeof(data));
                            if (data.MsgType == COMMAND){
                                receivecb(data);
                                /*for(int i=0;i<data.size;++i){
                                    std::cout << data.buffer[i];
                                }
                                std::cout << "\n";*/
                            }
                            else{
                                std::cout << "msge is not data type\n";
                            }
                        }
                        else if (msgrxv.ctrlMsge == CTRL_MSGE){

                        }
                        else{}

                        
                              
                    } 
                    else {
                        printf("Unexpected event occurred: %d\n", pfds[0].revents);
                    }   
               }
	
        memset(buffer,'0',MaxBufSize);
        if (UDCpayload.empty() ){
            msgrxv.ctrlMsge = CTRL_MSGE;
            memcpy( msgrxv.buffer,"CTRLMSGE",8);
            msgrxv.size = 8;
            memcpy(buffer,&msgrxv,sizeof(msgrxv) );
        }
        else{
            if (ignStatus ) { 
                Payload data = UDCpayload.back();
                UDCpayload.pop_back();
                msgrxv.size = data.size;
                msgrxv.ctrlMsge = DATA_MSGE;
                memcpy(&msgrxv.buffer,&data,sizeof(data));
                memcpy(&buffer,&msgrxv,sizeof(msgrxv) ); 
            }           
        }     
       int ret = send(client, buffer, bufsize, 0);
        if (ret != -1){
            // std::cout << "send to server\n";
        }
        else{
            std::cout <<"send failed\n";
        }      

    } while (!isExit);
    cout << "\n=> Connection terminated.\nGoodbye...\n";
    close(client);
}

void ComInterface::startThread()
{
    commThread = std::thread( [this]() {this->threadAction();}  );
    commThread.detach();
}

void ComInterface::closeConnection()
{
    isExit = true;
}
