
#ifndef COLLECTD_JOB_HPP
#define COLLECTD_JOB_HPP
#include <iostream>
#include <cstring>
#include <vector>

namespace DataPointConfiguration
{
    using TimeDeltaTriggerEvent = uint32_t;
    using SignalCollectionCount = uint32_t;
    enum class CollectionConfiguration:uint8_t{
        TimeDeltaTriggerEvent,SignalCollectionCount
    };
    typedef   struct {
        TimeDeltaTriggerEvent time_delta_milliseconds;
        SignalCollectionCount count;
    }Trigger;

    class DataPointConfigurationHandler{
        std::vector<uint32_t> triggerAnnotationIDs = {};
        std::vector<Trigger> event_trigger;
        Trigger trigger;       
        public:
        bool setTriggerAnnotationIDs(uint32_t );
        bool updateDataPointConfiguration(CollectionConfiguration configType,TimeDeltaTriggerEvent time = 0,\
                                                                            SignalCollectionCount count = 0 );
        bool getTriggerAnnotationIDs(std::vector<uint32_t>& );
        bool getDataPointConfiguration(CollectionConfiguration configType,TimeDeltaTriggerEvent time = 0,\
                                        SignalCollectionCount count = 0 );//for geo attributes add xtra agguments to hold the response
        bool CheckForPeriodicity();
    };
};


namespace CollectdSource
{
    enum  class CommandTypeEnum:uint8_t  {
        Undefined = 0,
        Getval = 1,
        Listval =2    
    } ;
    class Collectd    { 
        CommandTypeEnum commandtype;
        std::string identifier; 
        std::string DataSourceName;
        public:
        DataPointConfiguration::DataPointConfigurationHandler dataPointHandler;
        Collectd() {}
        bool setCommandType(uint8_t cType);
        bool setCollectdIdentifier(std::string identifier_); 
        bool setDataSourceName(std::string );
        bool getDataSourceName(std::string&);
    };
};



class JobConfig{
    std::string job_uuid;
    uint32_t job_priority;
    public:
    bool setJobID(std::string);
    bool setJobPriority(uint32_t);

    bool getJobID(std::string&);
    bool getJobPriority(uint32_t&);
};

//[542]
class DataPoints{
    std::vector<std::string> dataPoints = {};//To store data source name like collectd,ddr etc
    public:
    CollectdSource::Collectd collectd;//[]need to check]
    
    bool updateDatapoint(std::string);
    bool isDataPointEmpty();
    bool getDataPoint(std::string&);
};
//[494]
class CollectionTask{
    public:
    uint32_t taskID;
    DataPoints dataPoints;
    DataPointConfiguration::DataPointConfigurationHandler dpHandler;
};
//[442]
class CollectionAction{
    public:
    CollectionTask collection_tasks;
    //CollectionExtents min_split_frequency
    //CollectionExtents data_packetization_trigger
};

namespace ValidityRestriction
{ 
    enum class System_States:uint8_t{    
        IGN_LOCK = 0,
        IGN_OFF = 1,
        IGN_ACC = 2,
        IGN_ON = 3,
        IGN_START = 4,
        IGNITION_OFF = 5	
    };

    class JobValidityRestrictions{
        public:
        System_States invalid_collection_states;/*In proto its an array of System_States.Need to check that use case.*/
        //CompositeTimeRange
        //CompositeLocation
        //MapRestriction
        bool setSystermstate(uint8_t state){
            this->invalid_collection_states = static_cast<System_States>(state);
            return true;
        }

    };
};

/***************************end of validity restrictions section*******************************************/

typedef struct  {
	uint64_t count ;

	//In bytes
	uint64_t size_byte ;
	//In meters
	uint64_t path_length_m ;
	//In seconds
	uint64_t path_duration_s ;

    DataPointConfiguration::Trigger by_trigger;//its an array.need to change
	
}CollectionExtents;

class JobTerminationConditions{//[291]
    public:
    CollectionExtents extents;

    //CompositeTimeRange[to do]
    //CompositeLocation[to do]
    //logical_expression[to do]
};
/***************************end of JobTerminationConditions section*******************************************/
class DataCollectionJob{
    public:
    JobTerminationConditions termination_conditions;
    CollectionAction action;
    ValidityRestriction::JobValidityRestrictions validity_restrictions;
    JobConfig job_config ;
};




#endif
