#ifndef DATA_COLLECTION_HPP
#define DATA_COLLECTION_HPP
#include "JobContainer.hpp"
#include <iostream>
#include <string>

class DataCollectionGateWay{
    public:

    bool DataSourceInit(std::string,shared_ptr<DataCollectionJobsList>& jobInstance);

};






#endif