#ifndef __TCPCONNECT_H__
#define __TCPCONNECT_H__
#include "mysocket.h"
#include "IChannelCallBack.h"
#include "Channel.h"
#include "Epoll.h"
class TcpConnect 
	: public IChannelCallBack
{
private:
	int m_socket_;
	std::string m_ipAddress_;
	int m_port_;
public:
	// 
	TcpConnect(const int& thesocket,
				const std::string& ipaddress,
				const int& port);
	~TcpConnect();
	// 回调的信息处理
	bool ChannelCallBack(const int& thesocket);
	bool Run(const int& thesocket);
	int get_Socket();
};

#endif