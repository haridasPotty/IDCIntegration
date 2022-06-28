#include "CommManager.h"


CommnMngr* CommnMngr::singleton_= nullptr;
std::mutex CommnMngr::mutex_;


CommnMngr *CommnMngr::GetInstance()
{    
    std::lock_guard<std::mutex> lock(mutex_);
    if(singleton_==nullptr){
        singleton_ = new CommnMngr();
    }
    return singleton_;
}

void CommnMngr::queueMonitoring(){
   while(!ignStatus){
        if (vCommand.empty()){
       // std::cout << "empty\n";
        }
    else{
        std::string cmd = vCommand.back();
        vCommand.pop_back();
        std::cout << "[" << cmd  <<"]\n";

        int x = cmd.compare("IGN_ON");
            if (x==0){
                std::cout << "Ignited....!\n";
                    ignStatus = true;
                    x=-1;
            }
            x = cmd.compare("IGN_OFF");
            if (x==0){            
                    raise(SIGUSR1);
                    x=-1;
            }        
        }       
   }
}
void CommnMngr::receivecb(Payload& msg)
{
   //std::cout << "UDC core:Commn Manager\n";
   Payload data;
   memcpy(&data,&msg,sizeof(msg));
   
  
   if (data.MsgType == COMMAND){
      char command[ data.size] ;
      memcpy(command,data.buffer,data.size);
      this->vCommand.push_back(command);
    }

   if (vCommand.empty()){
       std::cout << "empty\n";
    }
   else{
       std::string cmd = vCommand.back();
       vCommand.pop_back();
       std::cout << "[" << cmd  <<"]\n";
        this->currentIGNstate = cmd;
       int x = cmd.compare("IGN_ON");
       if (x==0){
           std::cout << "Ignited....!\n";
            ignStatus = true;
       }
        x = cmd.compare("IGN_OFF");
       if (x==0){
           
            raise(SIGTERM);
       } 
       
    }
}

