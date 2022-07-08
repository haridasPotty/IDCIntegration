#include "Job.hpp"

namespace CollectdSource
{
    bool Collectd::setCollectdIdentifier(std::string identifier_){
        this->identifier = identifier_;
        return true;
    }

    bool Collectd::setCommandType(uint8_t cType){
        this->commandtype = static_cast<CommandTypeEnum>(cType);
        return true;
    }

    bool Collectd::setDataSourceName(std::string arg ){
        this->DataSourceName = arg;
    }
    bool Collectd::getDataSourceName(std::string& arg) {
            arg = DataSourceName;
            return true;
     }
};
/******************End of CollectdSource*****************************************************/
namespace DataPointConfiguration
{
    bool DataPointConfigurationHandler::setTriggerAnnotationIDs(uint32_t arg1){
        triggerAnnotationIDs.push_back(arg1);
        return true;
    }

    bool DataPointConfigurationHandler::updateDataPointConfiguration( 
        CollectionConfiguration configType,TimeDeltaTriggerEvent time,
                                        SignalCollectionCount count  ){
        if (configType == CollectionConfiguration::TimeDeltaTriggerEvent){
            this -> trigger.time_delta_milliseconds = time;
            return true;
        }
        else if (configType == CollectionConfiguration::SignalCollectionCount){
            this -> trigger.count = count;
            return true;
        }
        else{
            return false;
        }      
    }

    bool DataPointConfigurationHandler::getTriggerAnnotationIDs(std::vector<uint32_t>&  annotationIDHolder){
        annotationIDHolder = this->triggerAnnotationIDs;
        return true;
    }
    bool DataPointConfigurationHandler::getDataPointConfiguration(CollectionConfiguration configType,\
                                                    TimeDeltaTriggerEvent time,SignalCollectionCount count){
        if(configType == CollectionConfiguration::TimeDeltaTriggerEvent){
            time = this->trigger.time_delta_milliseconds;
            return true;
        }
        else if(configType == CollectionConfiguration::SignalCollectionCount){
            count = this->trigger.count;
            return true;
        }
        else{
            return false;
        }                                                  
        
    }


};
/******************End of DataPointConfiguration*****************************************************/

bool JobConfig::setJobID(std::string jID){
    this->job_uuid = jID;
    return true;
}

bool JobConfig::setJobPriority(uint32_t jPriority){
     this->job_priority = jPriority;
     return true;
}

bool JobConfig::getJobID(std::string& jID){
    jID = this->job_uuid;
    return true;
}
bool JobConfig::getJobPriority(uint32_t& jPriority){
    jPriority = this->job_priority;
    return true;
}

/******************End of JobConfig*****************************************************/
