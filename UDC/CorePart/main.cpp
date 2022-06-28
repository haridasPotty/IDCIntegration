#include "StateMachine.hpp"

#include "statemachine.hpp"

#include "CommManager.h"

#include <memory>


    
int main(){
  SM1driver obj;
  SM1driver::registerHandler(&obj); 
  
  Timer::TimerHandler objTimer; timer_t TimerID;
  //objTimer.makeTimer(&TimerID,1000, 1000, &Timer::TimerHandler::timerHandler1,SIGRTMAX);
  

  
  
  CommnMngr* commPtr = CommnMngr::GetInstance();
  if (commPtr != nullptr) { 
    commPtr->ConnectServer();
    commPtr->startThread();       
    Payload udcpayload;
      udcpayload.MsgType = LOG;
      memcpy(udcpayload.buffer,"UDC start",size_t(9));
      udcpayload.size = 9;
    commPtr->SendUDCData((udcpayload) );
    commPtr->SendUDCData((udcpayload) );
    while(!commPtr->ignStatus){    
    } 
    obj.smStartThread();
    commPtr->SendUDCData((udcpayload) );    
    objTimer.makeTimer(&TimerID,1000, 1000, &Timer::TimerHandler::timerHandler1,SIGRTMAX);     
  }
  else{
    std::cout << "handler is null\n";
  }
  std::cout  << "[Good Bye]" <<"\n";
    return 0;
}
