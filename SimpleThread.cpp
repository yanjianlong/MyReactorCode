#include "SimpleThread.h"
namespace util{

CSimpleThread::CSimpleThread(const std::string& thread_name)
	: m_bRun_(true)
	, m_thread_handle_(0)
	, m_thread_id_(0)
	, m_thread_name_(thread_name)
{
	//std::cout << "thread create" << std::endl;
}

CSimpleThread::~CSimpleThread()
{
	//std::cout << "thread delete" << std::endl;
}

void CSimpleThread::StartThread()
{
	std::cout << GetThreadName() << " thread start " << std::endl;
	m_thread_id_ = pthread_create(&m_thread_handle_, NULL, &run_thread, this);
}

void* CSimpleThread::run_thread(void* param)
{
	CSimpleThread* my_thread = (CSimpleThread*)param;
	// while(my_thread->m_bRun_)
	my_thread->run_function();
	
}

std::string CSimpleThread::GetThreadName()
{
	return m_thread_name_;
}

void CSimpleThread::StopThread()
{
	if (m_bRun_)
		std::cout << GetThreadName() << " thread end result:"
				<< pthread_join(this->m_thread_id_, NULL) << endl;
	m_bRun_ = false;
}
}
