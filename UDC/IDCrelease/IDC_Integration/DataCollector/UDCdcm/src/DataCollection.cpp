#include "DataCollection.hpp"

  bool DataCollectionGateWay::DataSourceInit(std::string uid,\
                 shared_ptr<DataCollectionJobsList>& jobInstance){                   
    int compStatus = uid.compare("someip");
      if (1){
      //vdc interaction 
      if(jobInstance!=nullptr){ 

      std::cout << "[" << jobInstance->job.jobinfo.job_uuid<<"]\n";     
      }
      else{
      std::cout << "jobInstance is null\n";
      }  
            std::cout << "VDC interaction pending!!!\n";
    }
    else{
        std::cout << " UID mismatching\n";
        return false;
    }
      return true;
  }
 

