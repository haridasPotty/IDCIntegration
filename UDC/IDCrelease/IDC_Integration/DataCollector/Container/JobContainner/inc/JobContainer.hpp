#ifndef JOB_CONTAINER_HPP
#define JOB_CONTAINER_HPP
#include <vector>
#include <iostream>
#include <signal.h>
#include <time.h>
#include <memory>
#include <unistd.h>
#include <tuple>
#include <iterator>
#include "Job.hpp"
using namespace std;

namespace JobInstanceHandler
{
    enum jobType {ACTIVE,INVALID,PAUSED};
    class JInterface{
        public:       
        typedef tuple <std::string, int32_t, shared_ptr<DataCollectionJobsList> >  my_tuple;
        my_tuple jobContainertple;
        std::vector< my_tuple > jobInstanceVector;
        std::vector< my_tuple > ::iterator vItr;
        virtual void AddJob(std::string, int32_t, shared_ptr<DataCollectionJobsList>&) = 0;
        virtual bool GetJob(std::string,shared_ptr<DataCollectionJobsList>&  ) = 0; 
        virtual bool RemoveJob(std::string) = 0;    
             
    };
    class PausedJob:public JInterface{
        public:
        void AddJob(std::string uid, int32_t priority ,\
                         shared_ptr<DataCollectionJobsList>& jobInstance){                                                       
           jobContainertple = make_tuple(uid,priority,move(jobInstance));                        
           jobInstanceVector.push_back(move(jobContainertple));     
        }       
        
        bool GetJob(std::string uid,shared_ptr<DataCollectionJobsList>& jobInstance){                                 
             if(jobInstanceVector.empty())  {
                std::cout << "PauseJob container empty\n";
                return false;
            }
            else{ 
                    for (int j=0;j<jobInstanceVector.size();++j){                    
                        int status = uid.compare(get<0>(jobInstanceVector.at(j)) );
                        if (!status){                                            
                        jobInstance = ((get<2>(jobInstanceVector.at(j))));                                         
                            return true;
                        }
                    } 
            }                
            return false;
        } 
        bool RemoveJob(std::string uid){
            int status = -1;
            if(jobInstanceVector.empty())  {
                std::cout << "PauseJob container empty\n";
                return false;
            }
            else{
                for (auto itr = jobInstanceVector.begin(); itr != jobInstanceVector.end(); ++itr){
                        status = uid.compare(get<0>(*itr));
                        if( !status){
                            jobInstanceVector.erase(itr);
                            return true;
                        }
                    }          
            }
            return false;
        }      
    };

    class ActiveJob:public JInterface{
        public:
        void AddJob(std::string uid, int32_t priority ,\
                         shared_ptr<DataCollectionJobsList>& jobInstance){                                                       
           jobContainertple = make_tuple(uid,priority,move(jobInstance));                        
           jobInstanceVector.push_back(move(jobContainertple));     
        } 
        
       bool GetJob(std::string uid,shared_ptr<DataCollectionJobsList>& jobInstance){                                 
            if(jobInstanceVector.empty())  {
                std::cout << "ActiveJob container empty\n";
                return false;
            }
            else{ 
                    for (int j=0;j<jobInstanceVector.size();++j) {                    
                        int status = uid.compare(get<0>(jobInstanceVector.at(j)) );
                        if (!status){                                                 
                        jobInstance = ((get<2>(jobInstanceVector.at(j))));                                                     
                        return true;
                        }
                    } 
            }                
            return false;
        }  
        bool RemoveJob(std::string uid){
            int status = -1;
            if(jobInstanceVector.empty())  {
                std::cout << "ActiveJob container empty\n";
                return false;
            }
            else{
                for (auto itr = jobInstanceVector.begin(); itr != jobInstanceVector.end(); ++itr){
                        status = uid.compare(get<0>(*itr));
                        if( !status){
                            jobInstanceVector.erase(itr);
                            return true;
                        }
                    }          
            }
            return false;
        }       
    };

  
     class JobUpdateHandler{	
	    static JInterface* ptr[3] ;
        static ActiveJob active;
        static PausedJob paused;     
        
        public:
        JInterface* getInstance(jobType type){
            if (type == jobType::ACTIVE){               
                   ptr[0] = &active;               
                return ptr[0];
            }
            else if (type == jobType::INVALID){               
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
        ~JobUpdateHandler(){  		   
		}     
	
    };
};






namespace Timer{  
    typedef void (*t_somefunc)(int,siginfo_t*,void*);
    class TimerHandler{
            struct sigevent te;
            struct itimerspec its;
            struct sigaction sa;
        public:
            static int refCountvar;
        static void timerHandler1( int sig, siginfo_t *si, void *uc ){               
            refCountvar++;
            printf("%d\n",refCountvar);
        }
        static int getRefCount(){
            return refCountvar;
        }
        int makeTimer( timer_t *timerID, int expireMS, int intervalMS ,t_somefunc fnp,int number)
        {
            
            int sigNo = number;

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