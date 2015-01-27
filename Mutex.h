#ifndef __MUTEX_H__
#define __MUTEX_H__
#include "stdafx.h"
namespace util{

class CLock
{
private:
	pthread_mutex_t	m_mutex_;
public:
	CLock() { pthread_mutex_init(&m_mutex_, NULL); }
	~CLock() { pthread_mutex_destroy(&m_mutex_); }
	void Lock() { pthread_mutex_lock(&m_mutex_); }
	void UnLock() { pthread_mutex_unlock(&m_mutex_); }
};

class CMutex
{
private:
	CLock& m_lock_;
public:
	CMutex(CLock& lock)
		: m_lock_(lock)
	{
		m_lock_.Lock(); 
	}
	~CMutex() 
	{ 
		m_lock_.UnLock();
	}
};

}


#endif
