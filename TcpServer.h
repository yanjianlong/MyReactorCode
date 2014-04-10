#ifndef __TCPSERVER_H__
#define __TCPSERVER_H__
#include "Accepter.h"
#include "TcpConnect.h"
#include "EventLoop.h"
class TcpServer 
	: public IAccepterCallBack
{
private:
	// 服务端套接字
	Accepter* m_Accepter_;
	// 客户端套接字
	std::map<int, TcpConnect*> m_MapTcpConnect_;

	// Epoll_Event
	EventLoop* m_loop_;			//事件循环

	//EpollEventCallBack m_CallBack_;	// 回调删除函数
public:
	TcpServer(const std::string& ipAddress, const int& port, const bool& block);
	~TcpServer();
	void Start();									// 服务启动
	// 	new Connecter callback function
	bool newConnectCallBack(const int& thesocket,
							const std::string& ipaddress,
							const int& port);	// 回调函数

	bool DeleteConnect(const int& thesocket);
};
#endif