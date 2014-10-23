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
	Epoll* m_epoll_;			// epoll
	// 用户服务器回调
	IServerUserCallBack* m_UserServerCallBack_;

	// 初始化server
	void Init(const std::string& ipAddress, 
				const int& port, const bool& block, const int& max_event);

public:
	//TcpServer();
	TcpServer(const std::string& ipAddress, const int& port, const bool& block, const int& max_event);
	~TcpServer();
	
	// 初始化服务器
	// void InitServer(const std::string& ipAddress, 
	// 			const int& port, const bool& block);
	void Start();									// 服务启动
	// 	new Connecter callback function
	bool newConnectCallBack(const int& thesocket,
							const std::string& ipaddress,
							const int& port);	// 回调函数

	bool DeleteConnectCallBack(const int& thesocket);
	// 设置服务回调
	void set_ServerCallBack(IServerUserCallBack* theCallBack);
};
#endif