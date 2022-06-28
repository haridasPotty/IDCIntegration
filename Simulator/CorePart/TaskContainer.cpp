#include "TaskContainer.hpp"
namespace TaskContainer{
    PeriodicTaskHandler TaskContainerHandler::pResponse;  
   // IncrementalResponseTaskHandler TaskContainerHandler::incrResponse;
  //  QuickResponseTaskHandler TaskContainerHandler::qResponse;
    TaskContainerInterface* TaskContainerHandler::ptr[3]  {nullptr}; 

        bool PeriodicTaskHandler:: IsEmpty() {
            if (TaskContainer.empty() ){
                return true;
            }
            return false;
        }
        bool PeriodicTaskHandler::PutInstance( unique_ptr<CollectdSource::Collectd> obj) {
            std::cout << "PeriodicTaskHandler PutTask invoked\n";
            TaskContainer.push_back(move (obj) );
            return true;
        }
        bool PeriodicTaskHandler::GetInstance(unique_ptr<CollectdSource::Collectd>& ptr) {
            if (TaskContainer.empty() == false){
               ptr = std::move( TaskContainer.back() );
               TaskContainer.pop_back();
               return true;
            }
            return false; 
        }

        uint8_t PeriodicTaskHandler::GetSize() {
             return (TaskContainer.size() );
        }

     /*   bool QuickResponseTaskHandler:: IsEmpty() {
            if (TaskContainer.empty() ){
                return true;
            }
            return false;
        }
        bool QuickResponseTaskHandler::PutTask( tType) {
            return true; 
        }
        bool QuickResponseTaskHandler::GetTask(tType&) {
            return true; 
        }

        bool IncrementalResponseTaskHandler:: IsEmpty() {
            if (TaskContainer.empty() ){
                return true;
            }
            return false;
        }
        bool IncrementalResponseTaskHandler::PutTask( tType) {
            return true; 
        }
        bool IncrementalResponseTaskHandler::GetTask(tType&) {
            return true; 
        }*/
};