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

	// 发送缓冲区
	std::string m_recvBuffer_;
	// 接收缓冲区
	std::string m_sendBuffer_;
	const int m_bufferSzie_;
	Channel* m_pChannel_;
	// 时间定时器
	int64_t m_TimeID_;
public:
	// 
	TcpConnect(const int& thesocket,
				const std::string& ipaddress,
				const int& port);
	~TcpConnect();
	// 回调的信息处理
	bool RecvDataCallBack(const int& thesocket);
	bool SendDataCallBack(const int& thesocket);
	
	bool Run(const int& thesocket);
	int get_Socket();

	// 设置服务回调
	void set_ServerCallBack(IServerUserCallBack* theCallBack);
	// 回调连接事件
	void handleConnnectCallBack();

	// 发送数据
	bool sendBuffer(const int& thesocket);
};

#endif