#include "UserServer.h"

#include <signal.h>

UserServer* myServer = NULL;
static void sig_int(int num)
{
	std::cout << num << std::endl;
	if (NULL != myServer)
		delete myServer; 
}
int main()
{
	myServer = new UserServer("192.168.189.129", 8080, true, 10240);
	signal(SIGINT, sig_int);
	myServer->StartServer();
	return 0;
}

