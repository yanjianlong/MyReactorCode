#ifndef __LOG_THREAD__
#define __LOG_THREAD__
#include "SimpleThread.h"
#include "Mutex.h"

namespace util{

class CLogThread:
	public CSimpleThread
{
private:
	static CLogThread* m_instance_;
	CLock m_buffer_lock_;
	std::vector<string> m_store_buffer_;
	std::vector<string> m_write_buffer_;
	CLogThread();
	void Log(const string& level, const string& contetn);
	// std::string m_file_name_;

	void CheckFile();
	FILE* m_fd_;

public:
	static CLogThread* GetInstance();
	~CLogThread();
	void run_function();		//	thread function
};

}

#define LOG_DEBUG(content) util::CLogThread::GetInstance()->Log("DEBUG", content)
#define LOG_INFO(content) util::CLogThread::GetInstance()->Log("INFO", content)
#define LOG_WARNING(content) util::CLogThread::GetInstance()->Log("WARNING", content)
#define LOG_ERROR(content) util::CLogThread::GetInstance()->Log("ERROR", content)
#define LOG_FATAL(content) util::CLogThread::GetInstance()->Log("FATAL", content)

#endif