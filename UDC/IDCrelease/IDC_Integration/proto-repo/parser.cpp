///g++ -std=c++17 -I Proto/  parser.cpp Job.cpp Proto/*.pb.cc -o ProtoExe `pkg-config --cflags --libs protobuf`

#include <iostream>
#include <fstream>
#include <ostream>
#include <vector>
#include "backend_message_format.pb.h"   

#include "data_collection_configuration_request.pb.h"

#include "data_types.pb.h"

#include "logical_expression.pb.h"

#include "signal_source_definition.pb.h"

#include "static_config_udc_civic.pb.h"

#include "Job.hpp"

using namespace std;
class ReqParser{
public:
DataCollectionJobsListMessage jobHandler;

data_collection_configuration_request::DataCollectionJob::JobConfig jobconfig;
data_collection_configuration_request::DataCollectionJob job;
signal_source_definition::CollectdSource collectd;
data_collection_configuration_request::Datapoint datapointCollectd;
data_collection_configuration_request::DatapointsConfiguration dpConfig;
data_collection_configuration_request::CollectionTask collectiontask;
data_collection_configuration_request::Trigger trigger,termTrigger;
data_collection_configuration_request::TriggerAnnotationID id1,id2;
data_collection_configuration_request::CollectionAction collectionaction;
data_collection_configuration_request::JobValidityRestrictions validityRestr;
data_collection_configuration_request::JobTerminationConditions termCond;
data_collection_configuration_request::CollectionExtents collectionextend;
data_collection_configuration_request::SystemStates state;

const google::protobuf::Reflection* reflection = jobHandler.GetReflection();
const google::protobuf::Descriptor* descriptor = jobHandler.GetDescriptor();
const google::protobuf::FieldDescriptor* field = nullptr;

DataCollectionJob dcj;
const char *path="Proto/IDC_Config.data";

public:
void set(){ 
  jobconfig.set_job_priority(1);
  jobconfig.set_job_uuid("collectd");
  ///collectd.set_commandtype(signal_source_definition::CollectdSource::CommandTypeEnum::CollectdSource_CommandTypeEnum_Listval);
  ///collectd.set_identifier("cpuinfo");
  
  
  datapointCollectd.mutable_collectd()->set_identifier("cpuinfo");
  datapointCollectd.mutable_collectd()-> \
     set_commandtype(signal_source_definition::CollectdSource::CommandTypeEnum::\
                                          CollectdSource_CommandTypeEnum_Listval);
  
  /*end of data point*/
  collectiontask.set_task_id(12);
  collectiontask.add_data_points()->CopyFrom(datapointCollectd);
  

  /*Trigger*/  
  id1.set_id(12);//id2.set_id(24);
  trigger.add_trigger_annotation_ids()->CopyFrom(id1);
  //trigger.add_trigger_annotation_ids()->CopyFrom(id2);
  

  for (int i=0;i<trigger.trigger_annotation_ids_size();++i){
    //std::cout << trigger.mutable_trigger_annotation_ids(i)->DebugString();
  }

  trigger.mutable_time_delta_trigger_event()->set_time_delta_milliseconds(2000);    
  collectiontask.mutable_data_points_configuration()->add_event_trigger()->
                                                              CopyFrom(trigger);
  collectionaction.add_collection_tasks()->CopyFrom(collectiontask);  
   /*end of collection task*/
   /*validity restriction */
  state.set_state(data_collection_configuration_request::System_States::IGN_ACC);

  /*collection extend for temination condition*/
  //collectionextend.set_count(12);//need to collect 12 samples from the source
  //termCond.mutable_extents()->set_count(12);

  
#if 0
  job.mutable_job_config()->set_job_uuid("collectdJob");
  job.mutable_job_config()->set_job_priority(12);

  state.set_state(data_collection_configuration_request::System_States::IGN_ACC);
  validityRestr.add_invalid_collection_states()->CopyFrom(state);

  job.mutable_validity_restrictions()->add_invalid_collection_states()->CopyFrom(state);

  job.mutable_action()->add_collection_tasks()->set_task_id(121);
  job.mutable_action()->add_collection_tasks()->add_data_points()->CopyFrom(datapointCollectd);
  #endif
  job.mutable_job_config()->set_job_priority(12);
  job.mutable_job_config()->set_job_uuid("collectd");

  /*action*/
  job.mutable_action()->add_collection_tasks()->CopyFrom(collectiontask);

  /*validity restriction*/
  job.mutable_validity_restrictions()->add_invalid_collection_states()->CopyFrom(state);

  /*termination condition*/
  job.mutable_termination_conditions()->mutable_extents()->set_count(12);
  job.mutable_termination_conditions()->mutable_extents()->set_path_duration_s(1);

/*******************end of data_collection_config_req***************************************/

jobHandler.add_new_jobs()->CopyFrom(job);


/*jobHandler.add_job_ids_to_terminate()->append("sss");
jobHandler.add_job_ids_to_terminate()->append("collectd");*/ 
  

  
  ////////std::cout << jobHandler.DebugString();

  std::ofstream ofs(path/*"./Proto/IDC_Config.data"*/, std::ios_base::out | std::ios_base::binary);
  jobHandler.SerializeToOstream(&ofs);     

}

void Read(){
  fstream input(path/*"./Proto/IDC_Config.data"*/, ios::in | ios::binary);
    if (!jobHandler.ParseFromIstream(&input))    {
      std::cout << "Failed to parse IDC_Config.data file" << endl;    
    }

  const google::protobuf::FieldDescriptor* field = descriptor->field(0);  
  //std::cout <<  descriptor->field_count();
  for (int i=0;i<descriptor->field_count();++i){
    const google::protobuf::FieldDescriptor* field_desc = descriptor->field(i); 
    std::cout << field_desc->name()<<"\t"<<field_desc->type_name() <<"\t\n";
   }

   jobHandler.mutable_new_jobs(0)->mutable_action()->mutable_collection_tasks(0)->
          mutable_data_points(0)->mutable_collectd()->set_datasourcename("collectd");

  std::cout << jobHandler.new_jobs_size() << "\n";
  std::cout << jobHandler.mutable_new_jobs(0)->DebugString();


 for (int i=0; i<jobHandler.new_jobs_size();++i ) {   
   dcj.job_config.setJobPriority( jobHandler.mutable_new_jobs(i)-> \
                                              mutable_job_config()->job_priority() ); 
   dcj.job_config.setJobID( jobHandler.mutable_new_jobs(i)->mutable_job_config()-> \
                                                                        job_uuid() );
   dcj.validity_restrictions.setSystermstate(jobHandler.mutable_new_jobs(i)-> \
     mutable_validity_restrictions()->mutable_invalid_collection_states(0)->state());
   
   dcj.action.collection_tasks.taskID = jobHandler.mutable_new_jobs(i)-> \
                            mutable_action()->mutable_collection_tasks(i)->task_id();
                                                                                  
   dcj.action.collection_tasks.dataPoints.collectd.setCollectdIdentifier( \
     jobHandler.mutable_new_jobs(i)->mutable_action()->mutable_collection_tasks(i)->\
                          mutable_data_points(0)->mutable_collectd()->identifier()  );

    dcj.action.collection_tasks.dataPoints.collectd.setCommandType( \
     jobHandler.mutable_new_jobs(i)->mutable_action()->mutable_collection_tasks(i)->\
                          mutable_data_points(0)->mutable_collectd()->commandtype()  );

    dcj.action.collection_tasks.dpHandler.setTriggerAnnotationIDs( \
      jobHandler.mutable_new_jobs(i)->mutable_action()->mutable_collection_tasks(i)-> \
                        mutable_data_points_configuration()->mutable_event_trigger(0)->\                                                                                                 
                        mutable_trigger_annotation_ids(0)->id()    );
    dcj.action.collection_tasks.dpHandler.updateDataPointConfiguration( \ 
              DataPointConfiguration::CollectionConfiguration::TimeDeltaTriggerEvent, \
     jobHandler.mutable_new_jobs(i)->mutable_action()->mutable_collection_tasks(i)->  \ 
                      mutable_data_points_configuration()->mutable_event_trigger(0)-> \
                                time_delta_trigger_event().time_delta_milliseconds() );

   dcj.termination_conditions.extents.count = jobHandler.mutable_new_jobs(i)-> \
            mutable_termination_conditions()->mutable_extents()->count();
                                                             

   dcj.termination_conditions.extents.path_duration_s = jobHandler.mutable_new_jobs(i) ->\
      mutable_termination_conditions()->mutable_extents()->path_duration_s(); 

   std::cout <<  "termination count=" << dcj.termination_conditions.extents.count  << "\n"; 

 //  dcj.action.collection_tasks.dataPoints.collectd.setDataSourceName( \ 
    std::string <<  jobHandler.mutable_new_jobs(i)->mutable_action()->mutable_collection_tasks(i)->data_points();
   //);
   
 }
 

  
  //std::cout << jobHandler.mutable_new_jobs(0)->mutable_action()->mutable_collection_tasks(0)->task_id()<<"\n";

  //std::cout <<"--"<< jobHandler.mutable_new_jobs(0)->mutable_action()->mutable_collection_tasks(0)->data_points(0).signal_definition_case()<<"\n";

 /* if (jobHandler.mutable_new_jobs(0)->mutable_action()->mutable_collection_tasks(0)->data_points(0).signal_definition_case() \
         ==    10){
    std::cout << "collectd matching\n";
    std::cout << jobHandler.mutable_new_jobs(0)->mutable_action()->mutable_collection_tasks(0)->data_points(0).collectd().commandtype();
    std::string id = jobHandler.mutable_new_jobs(0)->mutable_action()->mutable_collection_tasks(0)->data_points(0).collectd().identifier();
    std::cout << "identifier"<< id << "\n";


  }*/

  //std::cout << jobHandler.mutable_new_jobs(0)->mutable_action()->mutable_collection_tasks(0)->data_points_configuration().event_trigger(0).trigger_annotation_ids_size()<<"\n";



  
  

   

  
  
  

}

};

int main()
{
ReqParser obj;obj.set();obj.Read();

return 0;
}