//g++ -std=c++17 -I Proto/ -I DataCollector/ DataCollector/*.cpp   Job.cpp Proto/*.pb.cc -o ProtoExe `pkg-config --cflags --libs protobuf`

#include "statemachine.hpp"

namespace StateControlVariable{
     int input  = 0;
};
 SM1driver* SM1driver::objHolder = nullptr;
 std::string EnumToStr( ValidityRestriction::System_States ignState){
    if (ignState == ValidityRestriction::System_States::IGN_ACC)
            return "IGN_ACC";
    else if (ignState == ValidityRestriction::System_States::IGN_LOCK)
            return "IGN_LOCK";
    else{}
}
bool status = false;bool status1 = false;
void LogToSimulator(const char* ptr,uint16_t length){
    CommnMngr* commPtr = CommnMngr::GetInstance();
    if (commPtr != nullptr){ 
    Payload udcpayload;
    udcpayload.MsgType = UPLOADMSGE;
    std::memcpy(udcpayload.buffer,ptr,length);
    udcpayload.size = length;
    commPtr->SendUDCData(udcpayload);
    }
    else{
    }
}



unique_ptr<StateMachine2>Idle ::onEvent(States state){    
    return make_unique<ModeSelector>();
}

unique_ptr<StateMachine2>ModeSelector ::onEvent(States state){  
    std::cout << "modeselector\n";
    return make_unique<ConfigManager>();
}

unique_ptr<StateMachine2>ConfigManager ::onEvent(States state){ 
    std::cout << "ConfigManager\n";
     ReqParser reqpObj;
    if (reqpObj.CheckForNewRequest() != true){
        return make_unique<DataCollector>();
    }
   unique_ptr<DataCollectionJob> jobInstance;
   jobInstance = std::make_unique<DataCollectionJob>();
   reqpObj.Read( jobInstance.get() ); 
   JobInstanceHandler::JobUpdateHandler obj;
   JobInstanceHandler::JInterface* jptr = \
                obj.getInstance(JobInstanceHandler::jobType::PAUSED);
   jptr ->PutInstance(std::move(jobInstance));
   return make_unique<TaskUpdater>();
}

unique_ptr<StateMachine2>TaskUpdater ::onEvent(States state){
    std::cout << "TaskUpdater\n";
    return make_unique<DataCollector>();
}

unique_ptr<StateMachine2>DataCollector ::onEvent(States state){
    std::cout << "DataCollector\n";
    unique_ptr<DataCollectionJob> jobInstance \
                     = std::make_unique<DataCollectionJob>();
    JobInstanceHandler::JobUpdateHandler obj;    
    JobInstanceHandler::JInterface* jptr =  \
                obj.getInstance(JobInstanceHandler::jobType::ACTIVE);
    if( jptr->IsEmpty() == false && status == true  ) {     
        jptr->GetInstance(jobInstance);
        std::string dataSource;        
            std::string id;
            jobInstance->job_config.getJobID(id) ;
            std::cout << "ID+" << id << "\n"; 
                CommnMngr* commPtr = CommnMngr::GetInstance();
                if (commPtr != nullptr && status1 == true){ 
                    Payload udcpayload;
                    udcpayload.MsgType = UPLOADMSGE;
                    std::memcpy(udcpayload.buffer,id.c_str(),id.length() );
                    udcpayload.size = id.length();
                    commPtr->SendUDCData(udcpayload);
                    status1 = false;
                }
    }
    else{        
    }

    int ref = Timer::TimerHandler::getRefCount();
    uint32_t timeTrigger = 6;
    jobInstance->action.collection_tasks.dpHandler.\
        getDataPointConfiguration(DataPointConfiguration:: \
            CollectionConfiguration::TimeDeltaTriggerEvent,timeTrigger);
    timeTrigger = timeTrigger/1000;
   
     /* if ( (ref%timeTrigger) == 0){
        std::cout << "[refCount matching----------------------]\n";
    }  */           
    return make_unique<PollingState>();
}


unique_ptr<StateMachine2>PollingState ::onEvent(States state){
    std::cout << "PollingState\n";
    int& ref = StateControlVariable::input;  
    ref=0;  
    CommnMngr* commPtr = CommnMngr::GetInstance();
    unique_ptr<DataCollectionJob> jobInstance \
                    = std::make_unique<DataCollectionJob>();

    JobInstanceHandler::JobUpdateHandler obj;
    JobInstanceHandler::JInterface* jptr =  \
                obj.getInstance(JobInstanceHandler::jobType::PAUSED);
    jptr->GetInstance(jobInstance);
    std::string ignState =  \
       EnumToStr(jobInstance->validity_restrictions.invalid_collection_states);
    if( ! (ignState.compare(commPtr->currentIGNstate) ) ){       
       std::cout << "validity test success\n";
       /*push the job into Active container*/
       jptr = obj.getInstance(JobInstanceHandler::jobType::ACTIVE);
       status = true;
       jptr->PutInstance( std::move(jobInstance) );
       
       
   }
   else{
       jptr = obj.getInstance(JobInstanceHandler::jobType::ACTIVE);
       jptr->ClearContainer();
       status = false;
       std::cout << "validity test failed\n";
       status1 = true;
       
   }     
    return make_unique<ModeSelector>();
}

unique_ptr<StateMachine2>FinalState ::onEvent(States state) {  
    return make_unique<ModeSelector>();
}

/*******************************************************************************************/
void SM1driver::smStartThread(){
     sm2Thread = std::thread( [this]() {this->sm1Driver();}  );
     sm2Thread.join();
}

/*
int main(){
  SM1driver obj;
  Timer::TimerHandler objTimer; timer_t TimerID;
  objTimer.makeTimer(&TimerID,2, 2, &Timer::TimerHandler::timerHandler1,SIGRTMAX);
  obj.sm1Driver(); 

    return 0;
}*/
