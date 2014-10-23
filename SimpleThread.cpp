#include "SimpleThread.h"
CSimpleThread::CSimpleThread(const std::string& thread_name)
	: m_bRun_(true)
	, m_thread_handle_(0)
	, m_thread_id_(0)
	, m_thread_name_(thread_name)
{
	std::cout << "thread create" << std::endl;

}

CSimpleThread::~CSimpleThread()
{
	std::cout << "thread delete" << std::endl;

}

void CSimpleThread::StartThread()
{
	m_thread_id_ = pthread_create(&m_thread_handle_, NULL, &run_thread, this);
}

void* CSimpleThread::run_thread(void* param)
{
	CSimpleThread* my_thread = (CSimpleThread*)param;
	std::cout << my_thread->GetThreadName() << " thread start " << std::endl;
	while(my_thread->m_bRun_)
		my_thread->run_function();
	std::cout << my_thread->GetThreadName() << " thread end " << std::endl;
}

std::string CSimpleThread::GetThreadName() const
{
	return m_thread_name_;
}