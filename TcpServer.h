#ifndef __TCPSERVER_H__
#define __TCPSERVER_H__
#include "mysocket.h"
#include "Channel.h"
class TcpServer : public IChannelCallBack
{
private:
	JianLongYanSocket m_MySocket_;	// 套接字
	std::string m_ipAddress_;		// ip地址
	int m_port_;					// 端口
	bool m_bBlock_;					// 是否阻塞
	int m_EpollFd_;					// epoll
public:
	TcpServer(const std::string& ipAddress, const int& port, const bool& block);
	~TcpServer();
	void Start();									// 服务启动
	// true	连接进行中
	// false 连接可以关闭了
	bool CallBackFunction(const int& thesocket);	// 回调函数
};
#endif