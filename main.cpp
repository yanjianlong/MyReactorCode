// #include "UserServer.h"

#include <signal.h>
#include "LogThread.h"
// 
// UserServer* myServer = NULL;
static void sig_int(int num)
{
	// std::cout << num << std::endl;
	// if (NULL != myServer)
	// 	delete myServer; 
}
class CMyServer
{
private:
	util::CLogThread* m_log_;

public:
	CMyServer()
		: m_log_(NULL)
	{
		m_log_ = new util::CLogThread("log_thread")
	}
	~CMyServer()
	{
		if (NULL !=  m_log_)
			delete m_log_;
		m_log_ = NULL;
	}
	void Start()
	{
		m_log_->StartThread()
	}

};

int main()
{

	// myServer = new UserServer("192.168.126.42", 8080, true, 10240);
	// signal(SIGINT, sig_int);
	// myServer->StartServer();
	cout << "test log threading" << endl;
	return 0;
}

