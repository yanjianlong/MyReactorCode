#include "TcpServer.h"
int main()
{
	TcpServer myServer("127.0.0.1", 8080, true);
	myServer.Start();
	return 0;
}