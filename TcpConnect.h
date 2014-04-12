#ifndef __TCPCONNECT_H__
#define __TCPCONNECT_H__
#include "mysocket.h"
#include "IChannelCallBack.h"
#include "Channel.h"
#include "Epoll.h"
#include "IServerUserCallBack.h"
class TcpConnect 
	: public IChannelCallBack
{
private:
	int m_socket_;
	std::string m_ipAddress_;
	int m_port_;
	IServerUserCallBack* m_UserServerCallBack_;
	// 回调发送事件
	void handleSendMessageCallBack(const int& thesocket,
						const std::string& recvData);
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

	// 设置服务回调
	void set_ServerCallBack(IServerUserCallBack* theCallBack);
	// 回调连接事件
	void handleConnnectCallBack();
};

#endif