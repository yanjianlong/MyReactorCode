#ifndef __JianLongYanSocket_H__
#define __JianLongYanSocket_H__
#include "stdafx.h"
class JianLongYanSocket
{
private:
	int m_Socket_;
public:
	JianLongYanSocket();
	~JianLongYanSocket();
	// 是否非阻塞
	bool createSocket(const bool& bNoneBlock);
	// 绑定套接字
	bool dobind(const std::string& ipAddress, const int& port);
	// 监听
	bool dolisten(const int& listenNumber);
	// 连接
	bool doconnect(const std::string& ipAddress, const int& port);
	// 接收
	void DoAccept();
	// 
	int get_Socket();
};
#endif