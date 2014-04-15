#ifndef __ACCEPTER_H__
#define __ACCEPTER_H__
#include "mysocket.h"
#include "IChannelCallBack.h"
#include "IAccepterCallBack.h"
#include "Epoll.h"
class Accepter 
	: public IChannelCallBack
{
public:
	Accepter(const std::string& ipAddress, 
			const int& port, const bool& bNonlock);
	~Accepter();
	// 运行 epoll池
	bool Run(const int& epollfd);
	// 本身回调
	bool RecvDataCallBack(const int& thesocket);
	bool SendDataCallBack(const int& thesocket);
	// 获取服务套接字
	int get_Socket();
	// set the callback function
	void set_CallBackFunction(IAccepterCallBack* theCallBack);
private:
	JianLongYanSocket m_serverSocket_;		// 套接字
	IAccepterCallBack* m_TcpServerCallBack_;// 服务回调
	std::string m_ipAddress_;		// ip地址
	int m_port_;					// 端口
	bool m_bNonBlock_;					// 是否阻塞
};
#endif