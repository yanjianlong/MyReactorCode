#ifndef __SIMPLETHREAD_H__
#define __SIMPLETHREAD_H__
#include "stdafx.h"
class CSimpleThread
{
private:
	bool m_bRun_;				// 是否运行
	pthread_t m_thread_handle_;		// 线程
	pid_t m_thread_id_;
	std::string m_thread_name_;
	static void* run_thread(void* param);	
public:
	CSimpleThread(const std::string& thread_name);
	virtual ~CSimpleThread();
	void StartThread();
	virtual void run_function() = 0;
	std::string GetThreadName() const;
};


#endif