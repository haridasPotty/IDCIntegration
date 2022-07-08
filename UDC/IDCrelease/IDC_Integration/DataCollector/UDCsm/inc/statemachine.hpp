//g++ -std=c++14 -Wall statemachine.cpp connhandler.cpp lcm.cpp Proto_file/test.pb.cc  -o test `pkg-config --cflags --libs protobuf`

//g++ -std=c++17 -I Proto/ -I DataCollector/ DataCollector/*.cpp   Job.cpp Proto/*.pb.cc -o ProtoExe `pkg-config --cflags --libs protobuf`
#ifndef STATEMACHINE_HPP
#define STATEMACHINE_HPP
#include <memory>
#include <iostream>
#include <csignal>
#include <stdlib.h>
#include <unistd.h>
#include <thread>

#include "JobContainer.hpp"
#include "DataCollection.hpp"
//#include "TimerHandler.hpp"
#include "Job.hpp"
#include "Parser.hpp"
#include "CommManager.h"
using namespace std;




enum States {ModeSelection,ConfigMngr,TaskUpdate,DataCollection,Polling,End};
namespace StateControlVariable{
    extern int input ;
};

class StateMachine2{
    public:
    virtual unique_ptr<StateMachine2> onEvent(States state) = 0; 
    
};

/* --------------------------------- SM States------------------------------------------ */
class Idle : public StateMachine2{
    public:
    unique_ptr<StateMachine2>  onEvent(States state) ;
};

class ModeSelector : public StateMachine2{
    public:
    unique_ptr<StateMachine2>  onEvent(States state) ;
};

class ConfigManager : public StateMachine2{
    public:   
    unique_ptr<StateMachine2>  onEvent(States state) ;        
};


class TaskUpdater :public  StateMachine2 {    
    public:
    unique_ptr<StateMachine2>  onEvent(States state) ;
};


class DataCollector :public StateMachine2 {    
    public:
    unique_ptr<StateMachine2>  onEvent(States state) ;
};

class PollingState :public StateMachine2 {    
    public:
    unique_ptr<StateMachine2>  onEvent(States state) ;    
};


class FinalState :public StateMachine2{
    public:  
    unique_ptr<StateMachine2>  onEvent(States state) ;    
};

/******************statemachie driver **********************************/



 class SM1driver : public StateMachine2{  
     public:
   int& ref1 = StateControlVariable::input; 
   std::thread sm2Thread;
   void smStartThread();
     
    static SM1driver* objHolder;  
    public:
	unique_ptr<StateMachine2> m_curr_state = make_unique<Idle>();
    unique_ptr<StateMachine2>  onEvent(States state) {return nullptr;}  
    SM1driver(){        
        signal(SIGTERM, &SM1driver::sigtermHandler);        
    } 
    static void registerHandler(SM1driver* objRef){
        objHolder = objRef;
    }   

    static void sigtermHandler(int signum){
        std::cout << "sigtermHandler invoked\n"; 
        objHolder->ref1 = 8;                        
    }

    void shutdown(){
        std::cout << "shutdown invoked\n";        
    }
        
	void dispatch(States e) {    
        auto new_state = m_curr_state->onEvent(e);
        if (new_state) {
            m_curr_state = move(new_state);
        }           
    }    
    bool sm1Driver(){
        SM1driver bl;
        bl.registerHandler(this);
        bool status = true;
        while(status){  
            if (ref1 <= 6 ) {         
                bl.dispatch( static_cast<States>(ref1));
                
            }
            else{
                status = false;           
            }           
            (ref1)++;
        }
        std::cout << "UDC core stopped\n";
        return true;
    }
};

#endif
