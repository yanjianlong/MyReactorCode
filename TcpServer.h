#ifndef __TCPSERVER_H__
#define __TCPSERVER_H__
#include "mysocket.h"
#include "IChannelCallBack.h"
class TcpServer
	: public IChannelCallBack
{
private:
	JianLongYanSocket m_MySocket_;
	std::string m_ipAddress_;		// ip地址
	int m_port_;					// 端口
	bool m_bBlock_;					// 是否阻塞
	int m_EpollFd_;					// epoll
public:
	TcpServer(const std::string& ipAddress, const int& port, const bool& block);
	~TcpServer();
	void Start();
	void CallBackFunction();
};
#endif