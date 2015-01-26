#include "LogThread.h"
namespace util{
CLogThread::CLogThread(const std::string& thread_name)
	: CSimpleThread(thread_name)
{
	cout << "CLogThread::CLogThread() create" << endl;
}
CLogThread::~CLogThread()
{
	cout << "CLogThread::~CLogThread() release" << endl;
}

void CLogThread::run_function()
{
	while(this->m_bRun_)
	{
		cout << "" << endl;
	}
}

}
