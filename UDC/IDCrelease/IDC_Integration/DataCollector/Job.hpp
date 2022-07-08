
#ifndef JOB_HPP
#define JOB_HPP
#include <iostream>
#include <cstring>
#include <vector>
#include <memory>
using namespace std;
typedef struct  {
	int32_t serviceid;
	int32_t eventid;
	std::string signalname;
}NetworkSignal;

typedef struct  {
	int32_t serviceid;
	int32_t eventid;
	std::string signalname;
}Collectd;

class TaskInfo{   
  
public:
    vector<NetworkSignal> nwSignalVector;
    bool NWsgnalUpdate(NetworkSignal nwsig){
        nwSignalVector.push_back(nwsig);
        return true;
    }
};

class JobConfigInfo{
public:
    string job_uuid;
    int32_t priority;
    TaskInfo task;    
};

class CollectionJob{
    public:
    JobConfigInfo jobinfo;
};

class DataCollectionJobsList{
public:
CollectionJob job;
std::string terminationJob;
};



#endif
