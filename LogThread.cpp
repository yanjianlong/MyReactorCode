#include "LogThread.h"
namespace util{

CLogThread* CLogThread::m_instance_ = NULL;
CLogThread::CLogThread()
	: CSimpleThread("LogThread")
	// , m_file_name_("")
	, m_fd_(NULL)
{
	cout << "CLogThread::CLogThread() create" << endl;
}

CLogThread::~CLogThread()
{
	if (NULL != m_fd_)
	{
		fclose(m_fd_);
	}
	cout << "CLogThread::~CLogThread() release" << endl;
}

CLogThread* CLogThread::GetInstance()
{
	static CLogThread log_thread;
	if (NULL == m_instance_)
		m_instance_ = &log_thread;
	return m_instance_;
}

void CLogThread::run_function()
{
	while(this->BoolRun())
	{
		CheckFile();
		sleep(0.5);
	}
}

void CLogThread::CheckFile()
{
	static struct tm pre_time;
	time_t t;
	time(&t);
	struct tm* cur_time = localtime(&t);
	if (pre_time.tm_year != cur_time->tm_year || pre_time.tm_mon != cur_time->tm_mon
		|| pre_time.tm_mday != cur_time->tm_mday)
	{
		char name[100] = {0};
		sprintf(name, "%d_%d_%d.log", cur_time->tm_year + 1900, cur_time->tm_mon + 1, cur_time->tm_mday);
		if (NULL != m_fd_)
			fclose(m_fd_);
		m_fd_ = fopen(name, "a+");
	}
	// cout << cur_time->tm_year << cur_time->tm_mon << cur_time->tm_mday << endl;
	memcpy(&pre_time, cur_time, sizeof(struct tm));
}

void CLogThread::Log(const string& level, const string& contetn)
{
}

}
