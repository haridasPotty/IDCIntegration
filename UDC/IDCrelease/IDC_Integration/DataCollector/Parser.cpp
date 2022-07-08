#include "Parser.hpp"

void ReqParser::set(){   

   // Request::NetworkSignal  network1,network2;
    network1.set_serviceid(12);
    network1.set_eventid(14);
    network1.set_signalname("nwsigname1");

    network2.set_serviceid(121);
    network2.set_eventid(141);
    network2.set_signalname("nwsigname2");

  //  Request::Collectd colectdinfo;
    colectdinfo.set_serviceid(22);
    colectdinfo.set_eventid(24);
    colectdinfo.set_signalname("collectd");

   // Request::TaskInfo task;
    task.set_taskid(51);
    task.add_network()->CopyFrom(network1);
    task.add_network()->CopyFrom(network2);

   // Request::JobConfig jconfig;
    jconfig.set_job_uuid("someip");
    jconfig.set_priority(1);
    jconfig.mutable_tasks()->set_taskid(120);
    jconfig.mutable_tasks()->add_network()->CopyFrom(network1);
    jconfig.mutable_tasks()->add_network()->CopyFrom(network2);

    std::cout << "Task size is=" <<jconfig.mutable_tasks()->network_size() <<"\n";

  
   network1.set_eventid(121);
    std::ofstream ofs(path, std::ios_base::out | std::ios_base::binary);
    network1.SerializeToOstream(&ofs);   
    std::cout << network1.DebugString();     
}

void ReqParser::Read(DataCollectionJobsList* dcj){
  std::cout << "Readinvoked\n";
int numJobs = 1;
int numTask = 1;
NetworkSignal sig;
sig.eventid  =12;
sig.serviceid =123;
sig.signalname = "funID";


dcj->job.jobinfo.task.NWsgnalUpdate(sig);
dcj->job.jobinfo.job_uuid ="someip";
dcj->job.jobinfo.priority=12;
}

bool ReqParser::CheckForNewRequest(){
  //check for IDC_Config.Data.If exist return true else false
  return true;
  }

  int ReqParser::GetNumberofJobs(){
    
    return jobHandler.jobconfig_size();
  }

  bool ReqParser::GetJobUUID(std::vector<std::string>&& vectJobUUID){

    fstream input(path, ios::in | ios::binary);
    if (!jobHandler.ParseFromIstream(&input))    {
    std::cout << "Failed to parse IDC_Config.data file" << endl;  
    return false ;  
    }
    for(int i=0;i<jobHandler.jobconfig_size();++i){       
        vectJobUUID.push_back(jobHandler.mutable_jobconfig(0)->job_uuid() );
    }
    return true;
  }

  
