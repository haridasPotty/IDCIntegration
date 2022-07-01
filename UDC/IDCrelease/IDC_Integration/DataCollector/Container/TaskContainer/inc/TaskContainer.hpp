#ifndef TASK_CONTAINER_HPP
#define TASK_CONTAINER_HPP
#include <iostream>
#include <vector>
#include <memory>
#include "Job.hpp"
using namespace std;
namespace TaskContainer
{
    enum TaskType {PeriodicResponse,QuickResponse,IncrementalResponse};
    using tType = CollectdSource::Collectd;
    class TaskContainerInterface{
        public:
        std::vector< unique_ptr<CollectdSource::Collectd> > TaskContainer;
        virtual bool PutInstance( unique_ptr<CollectdSource::Collectd> obj) = 0;
        virtual bool GetInstance(unique_ptr<CollectdSource::Collectd>& ptr) = 0;
        virtual bool IsEmpty() = 0;
        virtual uint8_t GetSize() = 0;
    };

    class PeriodicTaskHandler : public TaskContainerInterface{
        public:
        bool IsEmpty()      ;
        bool PutInstance( unique_ptr<CollectdSource::Collectd> obj) ;
        bool GetInstance(unique_ptr<CollectdSource::Collectd>& ptr);
        uint8_t GetSize();
    };

    /*class QuickResponseTaskHandler : public TaskContainerInterface{
        public:
        bool IsEmpty()      ;
        bool PutTask( tType) ;
        bool GetTask(tType&) ;
    };
    class IncrementalResponseTaskHandler : public TaskContainerInterface{
        public:
        bool IsEmpty()      ;
        bool PutTask( tType) ;
        bool GetTask(tType&) ;
    };*/

    class TaskContainerHandler{
        static TaskContainerInterface* ptr[3] ;
        static PeriodicTaskHandler pResponse;
       // static QuickResponseTaskHandler qResponse;
       // static IncrementalResponseTaskHandler incrResponse;
        public:
        TaskContainerInterface* getInstance(TaskType type){
            if (type == TaskType::PeriodicResponse){ 
                if (ptr[0] == nullptr){
                    ptr[0] = &pResponse;
                }
                return ptr[0];
            }
            else if (type == TaskType::QuickResponse){
                if (ptr[1] == nullptr){
               // ptr[1] = &qResponse;
                }
                return ptr[1];  
            }
            else if (type == TaskType::IncrementalResponse){
                if (ptr[2] == nullptr){
               // ptr[2] = &incrResponse;
                }
                return ptr[2];  
            }
            else{
                return &pResponse;
            }
        } 
    };
};



#endif