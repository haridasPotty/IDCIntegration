
#include "Parser.hpp"

int main()
{
ReqParser obj;///obj.set();//obj.Read();

unique_ptr<DataCollectionJobsList> p = make_unique<DataCollectionJobsList>();
obj.Read(p.get());
std::cout << p->job.jobinfo.job_uuid;
std::cout << "bye\n";
return 0;
}
