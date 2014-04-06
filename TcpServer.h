#ifndef __TCPSERVER_H__
#define __TCPSERVER_H__
#include "Accepter.h"
#include "TcpConnect.h"
class TcpServer 
	: public IAccepterCallBack
{
private:
	// 服务端套接字
	Accepter* m_Accepter_;
	// 客户端套接字
	std::map<int, TcpConnect*> m_MapTcpConnect_;
	int m_EpollFd_;
public:
	TcpServer(const std::string& ipAddress, const int& port, const bool& block);
	~TcpServer();
	void Start();									// 服务启动
	// 	new Connecter callback function
	bool newConnectCallBack(const int& thesocket,
							const std::string& ipaddress,
							const int& port);	// 回调函数
};
#endif