#ifndef JOB_CONTAINER_HPP
#define JOB_CONTAINER_HPP
#include <vector>
#include <iostream>
#include <signal.h>
#include <time.h>
#include <memory>
#include <unistd.h>
#include "Job.hpp"
using namespace std;

namespace JobInstanceHandler
{
    enum jobType {ACTIVE,INVALID,PAUSED};
    class JInterface{
        public:
        std::vector< unique_ptr<DataCollectionJob> > jobInstanceVector;
        virtual void PutInstance( unique_ptr<DataCollectionJob> obj) = 0;
        virtual bool GetInstance(unique_ptr<DataCollectionJob>& ptr) = 0;
        virtual bool IsEmpty() = 0;
        virtual uint8_t GetSize() = 0;
        virtual void ClearContainer() = 0;
    };
    class PausedJob:public JInterface{
        public:
        void PutInstance( unique_ptr<DataCollectionJob> obj ){
            jobInstanceVector.push_back(move (obj) );
        }
        bool GetInstance(unique_ptr<DataCollectionJob>& ptr){
            if (jobInstanceVector.empty() == false){
                ptr = std::move( jobInstanceVector.back() );
                jobInstanceVector.pop_back();
                return true;
            }
            return false;            
        }
        uint8_t GetSize() {
             return (jobInstanceVector.size() );
        }

        bool IsEmpty(){
            if (jobInstanceVector.empty() ){
                return true;
            }
            return false;
        }
        void ClearContainer(){
            jobInstanceVector.clear();
        }
    };

    class ActiveJob:public JInterface{
        public:
        void PutInstance( unique_ptr<DataCollectionJob> obj ){
            jobInstanceVector.push_back(move (obj) );
        }
        bool GetInstance(unique_ptr<DataCollectionJob>& ptr){
            if (jobInstanceVector.empty() == false){
                ptr = std::move( jobInstanceVector.back() );
                jobInstanceVector.pop_back();
                return true;
            }
            return false;            
        }
        bool IsEmpty(){
            if (jobInstanceVector.empty() ){
                return true;
            }
            return false;
        }
        uint8_t GetSize() {
            return (jobInstanceVector.size() );
        }
         void ClearContainer(){
            jobInstanceVector.clear();
        }
    };

    /*************************************************************************/
     class JobUpdateHandler{	
	    static JInterface* ptr[3] ;
        static ActiveJob active;
        static PausedJob paused;
        //static InvalidJobHandler invalid;
        
        public:
        JInterface* getInstance(jobType type){
            if (type == jobType::ACTIVE){               
                   ptr[0] = &active;               
                return ptr[0];
            }
            else if (type == jobType::INVALID){
                //ptr[1] = &invalid;
                return ptr[1];  
            }
            else if (type == jobType::PAUSED){
                if (ptr[2] == nullptr){
                ptr[2] = &paused;
                }
                return ptr[2];  
            }
            else{
                return &active;
            }
        }        
	
		JobUpdateHandler(){}
        ~JobUpdateHandler()		{
		    ///std::cout<<"destructor invoked  \n";
            		   
		}     
	
    };
};





namespace JobUpdate
{ 
    enum jobType {ACTIVE,INVALID,PAUSED};
    using jType = unique_ptr<DataCollectionJob>;
    class JobUpdateInterface{
        public:
        std::vector<unique_ptr<DataCollectionJob>> JobVector = {};         
        virtual bool IsEmpty()      = 0;
        virtual bool PutJob( unique_ptr<DataCollectionJob>) = 0;
        virtual bool GetJob( unique_ptr<DataCollectionJob>&) = 0;        
    };

    class AcitveJobHandler: public JobUpdateInterface{
       
        public:
        bool IsEmpty() ;
        bool PutJob(unique_ptr<DataCollectionJob> Job) ;
        bool GetJob(unique_ptr<DataCollectionJob>& Job);
    };
    class PausedJobHandler: public JobUpdateInterface{
       
        public:
        bool IsEmpty() ;
        bool PutJob(unique_ptr<DataCollectionJob> Job) ;        
        bool GetJob(unique_ptr<DataCollectionJob>& Job);
    };
    class InvalidJobHandler: public JobUpdateInterface{
       
        public:
        bool IsEmpty()         ;
        bool PutJob(unique_ptr<DataCollectionJob> Job) ;
        bool GetJob(unique_ptr<DataCollectionJob>& Job);
    };
    
    /***********************************************************/
    class JobUpdateHandler{	
	    static JobUpdateInterface* ptr[3] ;
        static AcitveJobHandler active;
        static PausedJobHandler paused;
        static InvalidJobHandler invalid;
        
        public:
        JobUpdateInterface* getInstance(jobType type){
            if (type == jobType::ACTIVE){ 
              //  if (ptr[0] == nullptr){
                    ptr[0] = &active;
               // }
                return ptr[0];
            }
            else if (type == jobType::INVALID){
               // if (ptr[1] == nullptr){
                ptr[1] = &invalid;
               // }
                return ptr[1];  
            }
            else if (type == jobType::PAUSED){
                if (ptr[2] == nullptr){
                ptr[2] = &paused;
                }
                return ptr[2];  
            }
            else{
                return &active;
            }
        }        
	
		JobUpdateHandler(){}
        ~JobUpdateHandler()		{
		   // std::cout<<"destructor invoked  \n";
            		   
		}     
	
    };
};

/*************************************************************************************/

namespace Timer
{
    //   timer_t TimerID;
    //timer_t secondTimerID;
    //timer_t thirdTimerID;

   /* static void timerHandler( int sig, siginfo_t *si, void *uc ){
        printf("sighandler invoked\n");
        static int refCount;
        refCount++;
        printf("%d\n",refCount);
        
    }*/
   /* static void timerHandler1( int sig, siginfo_t *si, void *uc ){
        printf("***************************************************************************sighandler1 invoked\n");
        
        static int refCount;
        refCount++;
        printf("%d\n",refCount);
        
    }*/
    
   


    typedef void (*t_somefunc)(int,siginfo_t*,void*);

    class TimerHandler{
            struct sigevent te;
            struct itimerspec its;
            struct sigaction sa;
        public:
            static int refCountvar;
        static void timerHandler1( int sig, siginfo_t *si, void *uc ){
        /* printf("************************************************ \
                ***************************timerHandler invoked %d\n",refCountvar);   */        
            refCountvar++;
            printf("%d\n",refCountvar);
        }
        static int getRefCount(){
            return refCountvar;
        }
        int makeTimer( timer_t *timerID, int expireMS, int intervalMS ,t_somefunc fnp,int number)
        {
            /*struct sigevent te;
            struct itimerspec its;
            struct sigaction sa;*/
            int sigNo = number;//SIGRTMIN;

            /* Set up signal handler. */
            sa.sa_flags = SA_SIGINFO;
            sa.sa_sigaction = fnp;//timerHandler;
            sigemptyset(&sa.sa_mask);
            if (sigaction(sigNo, &sa, NULL) == -1) {
            perror("sigaction");
            }

            /* Set and enable alarm */
            te.sigev_notify = SIGEV_SIGNAL;
            te.sigev_signo = sigNo;
            te.sigev_value.sival_ptr = timerID;
            timer_create(CLOCK_REALTIME, &te, timerID);

            its.it_interval.tv_sec =0;
            its.it_interval.tv_nsec = intervalMS * 1000000;//500000000ns=500ms
            its.it_value.tv_sec = 0;
            its.it_value.tv_nsec =  expireMS * 1000000;
            timer_settime(*timerID, 0, &its, NULL);

            return 1;
        }
    };
    


};
    
  


#endif