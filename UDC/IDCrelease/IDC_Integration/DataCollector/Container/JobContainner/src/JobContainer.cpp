#include "JobContainer.hpp"
namespace JobInstanceHandler{ 
    JInterface* JobUpdateHandler::ptr[3]  {nullptr}; 
    ActiveJob JobUpdateHandler::active;  
    PausedJob JobUpdateHandler::paused;
    //InvalidJobHandler JobUpdateHandler::invalid;

}
namespace Timer
{
    int TimerHandler::refCountvar = 1;
}
/*
namespace JobUpdate{ 
    JobUpdateInterface* JobUpdateHandler::ptr[3]  {nullptr}; 
    AcitveJobHandler JobUpdateHandler::active;  
    PausedJobHandler JobUpdateHandler::paused;
    InvalidJobHandler JobUpdateHandler::invalid;
    
    bool AcitveJobHandler::IsEmpty(){
        if (JobVector.empty() ){
            return true;
        }
        return false;
    }
    bool AcitveJobHandler::PutJob(unique_ptr<DataCollectionJob> Job){
        std::cout << "AcitveJobHandler PutJob invoked\n";
        JobVector.push_back( std::move(Job));
        return true;
    }
    bool AcitveJobHandler::GetJob(unique_ptr<DataCollectionJob>& Job){
        std::cout << "AcitveJobHandler GettJob invoked\n";
        Job = std::move( JobVector.back() );
        return true;
    }

    bool PausedJobHandler::IsEmpty(){
        if (JobVector.empty() ){
            return true;
        }
        return false;
    }
    bool PausedJobHandler::PutJob(unique_ptr<DataCollectionJob> Job){
        std::cout << "PausedJobHandler PutJob invoked\n";
        JobVector.push_back(Job);
        return true;
    }
    bool PausedJobHandler::GetJob(unique_ptr<DataCollectionJob>& Job){
        std::cout << "PausedJobHandler GettJob invoked\n";
        Job = std::move( JobVector.back() );
        return true;
    }

    bool InvalidJobHandler::IsEmpty(){
        if (JobVector.empty() ){
            return true;
        }
        return false;
    }
    bool InvalidJobHandler::PutJob(unique_ptr<DataCollectionJob> Job){
        std::cout << "InvalidJobHandler PutJob invoked\n";
        JobVector.push_back(Job);
        return true;
    }
    bool InvalidJobHandler::GetJob(unique_ptr<DataCollectionJob>& Job){
        std::cout << "InvalidJobHandler GettJob invoked\n";
        Job = std::move( JobVector.back() );
        return true;
    }     
};

void Task1(JobUpdate::jobType jobtype,int value){
    JobUpdate::JobUpdateHandler obj1;
    JobUpdate::JobUpdateInterface* ptr = obj1.getInstance(jobtype);
    //ptr->PutJob(value);
}

void Task2(JobUpdate::jobType jobtype){
    JobUpdate::JobUpdateHandler obj1;
    JobUpdate::JobUpdateInterface* ptr = obj1.getInstance(jobtype);
    int a = 0;
    //ptr -> GetJob(a);
    std::cout<<a<<"\n";

}

void Task3(JobUpdate::jobType jobtype){
    JobUpdate::JobUpdateHandler obj1;
    JobUpdate::JobUpdateInterface* ptr = obj1.getInstance(jobtype);
    if (ptr->IsEmpty()){
        std::cout <<"Job of type"<<jobtype <<"is empty\n";
    }
}

#ifdef JobContainerTest
int main(){
   /* JobUpdate::JobUpdateHandler obj1; JobUpdate::JobUpdateInterface* ptr4,*ptr5;    
    JobUpdate::JobUpdateInterface* ptr = obj1.getInstance(JobUpdate::jobType::ACTIVE);
    JobUpdate::JobUpdateHandler obj2;
    JobUpdate::JobUpdateInterface* ptr1 = obj2.getInstance(JobUpdate::jobType::ACTIVE);
    //////////////////////////////////////////std::cout << ptr <<"\t" << ptr1 << "\n";

    ptr->PutJob(12);
    int a = 0;
    ptr1 -> GetJob(a);
    std::cout<<a<<"\n";
    ptr4 = obj1.getInstance(JobUpdate::PAUSED);
    ptr5 = obj1.getInstance(JobUpdate::PAUSED);
    ptr4->PutJob(25);
    ptr5->GetJob(a);
    std::cout << a << "\n";

    ptr1 -> GetJob(a);
    std::cout<<a<<"\n";*/
  /* Task1(JobUpdate::jobType::ACTIVE,32);Task2(JobUpdate::jobType::ACTIVE);
    Task1(JobUpdate::jobType::INVALID,124);Task2(JobUpdate::jobType::INVALID);
    Task2(JobUpdate::jobType::ACTIVE);
    Task3(JobUpdate::jobType::PAUSED);
    #ifdef macro
    std::cout << "macro test enabled\n";
    #endif
    return 0;
}
#endif*/