﻿// #include "UserServer.h"
#include "LogThread.h"   
#include <dlfcn.h>
// #include "LogThread.h"
// // 
// class CMyServer
// {
// private:
// 	util::CLogThread* m_log_;

// public:
// 	CMyServer()
// 		: m_log_(NULL)
// 	{
// 		m_log_ = util::CLogThread::GetInstance();
// 	}
// 	~CMyServer()
// 	{
// 		if (NULL !=  m_log_)
// 		{
// 			m_log_->StopThread();
// 			// delete m_log_;
// 		}
// 		m_log_ = NULL;
// 	}
// 	void Start()
// 	{
// 		m_log_->StartThread();
// 	}
// 	void Stop()
// 	{
// 		m_log_->StopThread();
// 	}

// };

// CMyServer* myserver = NULL;
// static void sig_int(int num)
// {
// 	if (NULL != myserver)
// 	{
// 		myserver->Stop();
// 	}
// }


int main()
{
	void *handle;
	char *error;
	
	// double (*cosine )(double);
	handle = dlopen("./lib/libs/liblog.so", RTLD_LAZY);
	if(!handle){
		fputs(dlerror(), stderr);
		cout << "error" << endl;
	 	return 0;
	}
	
	// cosine = dlsym(handle, "cos");
	// if((error = dlerror()) != NULL){
	// 	fputs(error, stderr);
	// 	exit(1);
	// }
	
	// printf("%f", (*cosine)(2, 0));
	
	dlclose(handle);
	cout << "success" << endl;
	return 0;
	// myserver = new CMyServer();
	// myserver->Start();
	// // myServer = new UserServer("192.168.126.42", 8080, true, 10240);
	// // signal(SIGINT, sig_int);
	// // myServer->StartServer();
	// cout << "test log threading" << endl;
	// if(NULL != myserver)
	// {
	// 	sleep(1);
	// 	myserver->Stop();
	// 	sleep(1);
	// 	delete myserver;
	// }
	// myserver = NULL;
	return 0;
}

