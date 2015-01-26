#ifndef __SIMPLETHREAD_H__
#define __SIMPLETHREAD_H__
#include "stdafx.h"
namespace util{

class CSimpleThread
{
private:
	bool m_bRun_;						// bool run or not
	pthread_t m_thread_handle_;		// 
	pid_t m_thread_id_;
	std::string m_thread_name_;
	static void* run_thread(void* param);	
public:
	CSimpleThread(const std::string& thread_name);
	virtual ~CSimpleThread();
	void StartThread();
	void StopThread();
	virtual void run_function() = 0;
	std::string GetThreadName() const;
	bool BoolRun() const { return m_bRun_; }
};

}



#endif