#include "DataCollection.hpp"

  bool DataCollectionGateWay::DataSourceInit(std::string uid,\
                 unique_ptr<DataCollectionJobsList>& jobInstance){                   
    int compStatus = uid.compare("someip");
    if (!compStatus){
            //vdc interaction 
            std::cout << "VDC interaction pending!!!\n";
    }
    else{
        std::cout << " UID mismatching\n";
        return false;
    }
      return true;
  }
 

