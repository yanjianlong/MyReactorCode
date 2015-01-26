#ifndef __LOG_THREAD__
#define __LOG_THREAD__
#include "SimpleThread.h"
namespace util{
	
class CLogThread:
	public CSimpleThread
{
private:
public:
	CLogThread(const std::string& thread_name);
	~CLogThread();
	void run_function();
};


}


#endif