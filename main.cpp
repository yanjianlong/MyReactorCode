#include "UserServer.h"
int main()
{
	UserServer myServer("127.0.0.1", 8080, true);
	myServer.StartServer();
	return 0;
}