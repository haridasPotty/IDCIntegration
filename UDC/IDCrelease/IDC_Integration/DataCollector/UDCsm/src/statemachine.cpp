//g++ -std=c++17 -I Proto/ -I DataCollector/ DataCollector/*.cpp   Job.cpp Proto/*.pb.cc -o ProtoExe `pkg-config --cflags --libs protobuf`

#include "statemachine.hpp"
namespace StateControlVariable{
     int input  = 0;
};
 SM1driver* SM1driver::objHolder = nullptr;
bool status = true;//need to remove

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
    int nJob = reqpObj.GetNumberofJobs();     
    JobInstanceHandler::JobUpdateHandler obj;
     JobInstanceHandler::JInterface* jptr = \
                obj.getInstance(JobInstanceHandler::jobType::PAUSED); 
     
    if (status){ 
     for (int i=0;i<nJob;++i){ 
         shared_ptr<DataCollectionJobsList> jobInstance;
        jobInstance =  make_shared<DataCollectionJobsList>();         
        reqpObj.Read(jobInstance.get(),i);       
        jptr->AddJob(jobInstance->job.jobinfo.job_uuid, \
        jobInstance->job.jobinfo.priority,jobInstance );
     }
     status = false;
    }
    

   /*   shared_ptr<DataCollectionJobsList> jobInstance1 = \
        make_shared<DataCollectionJobsList>();
        
        jptr->GetJob("nw",(jobInstance1));
        if(jobInstance1!=nullptr){ 
        
        std::cout << "[" << jobInstance1->job.jobinfo.job_uuid<<"]\n";
        vector<NetworkSignal> nwSignalVector = \
        jobInstance1->job.jobinfo.task.nwSignalVector;

        NetworkSignal nw = nwSignalVector.back();
        std::cout << "[ signal Details]\n";
        std::cout << nw.eventid << nw.serviceid << nw.signalname << "\n"; 
        }
        else{
            std::cout << "jobInstance1 is null\n";
        }  */

    
   return make_unique<TaskUpdater>();
}



unique_ptr<StateMachine2>TaskUpdater ::onEvent(States state){
    std::cout << "TaskUpdater\n";
    return make_unique<DataCollector>();
}

unique_ptr<StateMachine2>DataCollector ::onEvent(States state){
    std::cout << "DataCollector\n"; 
    DataCollectionGateWay gwayobj;
    JobInstanceHandler::JobUpdateHandler obj;
    shared_ptr<DataCollectionJobsList> jobInstance1 = \
    make_shared<DataCollectionJobsList>();
    JobInstanceHandler::JInterface* jptr = \
                obj.getInstance(JobInstanceHandler::jobType::PAUSED);      
    if (jptr->GetJob("someip",(jobInstance1)) ){ 
        gwayobj.DataSourceInit( jobInstance1->job.jobinfo.job_uuid,\
                      (jobInstance1) );
    }
    else{
        std::cout << "Getting the instance of the job failed\n";
    }

    if (jptr->GetJob("nw",(jobInstance1)) ){ 
        gwayobj.DataSourceInit( jobInstance1->job.jobinfo.job_uuid,\
                      (jobInstance1) );
    }
    else{
        std::cout << "Getting the instance of the job failed\n";
    }

    return make_unique<PollingState>();
}


unique_ptr<StateMachine2>PollingState ::onEvent(States state){
    std::cout << "PollingState\n";
    int& ref = StateControlVariable::input;  
    ref=0;      
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
