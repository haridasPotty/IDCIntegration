#include "JobContainer.hpp"
namespace JobInstanceHandler{ 
    JInterface* JobUpdateHandler::ptr[3]  {nullptr}; 
    ActiveJob JobUpdateHandler::active;  
    PausedJob JobUpdateHandler::paused;
}
namespace Timer
{
    int TimerHandler::refCountvar = 1;
}

