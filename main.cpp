// #include "UserServer.h"

#include <signal.h>
#include "LogThread.h"
// 
class CMyServer
{
private:
	util::CLogThread* m_log_;

public:
	CMyServer()
		: m_log_(NULL)
	{
		m_log_ = new util::CLogThread("log_thread");
	}
	~CMyServer()
	{
		if (NULL !=  m_log_)
		{
			m_log_->StopThread();
			delete m_log_;
		}
		m_log_ = NULL;
	}
	void Start()
	{
		m_log_->StartThread();
	}
	void Stop()
	{
		m_log_->StopThread();
	}

};

CMyServer* myserver = NULL;
static void sig_int(int num)
{
	if (NULL != myserver)
	{
		myserver->Stop();
	}
}


int main()
{
	myserver = new CMyServer();
	myserver->Start();
	// myServer = new UserServer("192.168.126.42", 8080, true, 10240);
	// signal(SIGINT, sig_int);
	// myServer->StartServer();
	cout << "test log threading" << endl;
	if(NULL != myserver)
	{
		myserver->Stop();
		delete myserver;
	}
	myserver = NULL;
	return 0;
}

