#ifndef PARSER_HPP
#define PARSER_HPP


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
#include "request.pb.h"
//#include "../proto-repo/request.pb.h"

using namespace std;
class ReqParser{
  Request::JobConfig jconfig;
  Request::TaskInfo task;
  Request::Collectd colectdinfo;
  Request::NetworkSignal  network1,network2;
  public:

  Request::DataCollectionJob jobHandler;
  const google::protobuf::Reflection* reflection = jobHandler.GetReflection();
  const google::protobuf::Descriptor* descriptor = jobHandler.GetDescriptor();
  const google::protobuf::FieldDescriptor* field = nullptr;
  const char path[128]="/home/lenovo/HARI/fsmBook/IDCrelease/IDC_Integration/DataCollector/IDC_Config.data";
public:
  void set();
  void Read(DataCollectionJobsList* dcj);
  bool CheckForNewRequest();

  int GetNumberofJobs();
  bool GetJobUUID(std::vector<std::string>&& vectJobUUID);

};

#endif
