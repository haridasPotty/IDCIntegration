#ifndef COMMN_MANAGER_HPP
#define COMMN_MANAGER_HPP
#include <memory.h>
#include <csignal>
#include "comm.h"
#include <mutex>


 class CommnMngr:public ComInterface
 {
  public:

  static CommnMngr* singleton_;
  static CommnMngr *GetInstance();
  static std::mutex mutex_;
  
  void receivecb(Payload&);
  std::thread th1;
  void queueMonitoring();
  vector<std::string> vCommand;
  std::string currentIGNstate;


  void startMonitorThread(){
       th1 = std::thread( [this]() {this->queueMonitoring();}  );
    th1.detach();
  }

  

 };




 #endif
