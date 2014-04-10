#ifndef __CHANNEL_H__
#define __CHANNEL_H__
#include "IChannelCallBack.h"
#include "stdafx.h"
class Channel
{
private:
	// 回调函数
	IChannelCallBack* m_CallBackFun_;
	int m_socket_;											// 套接字
	int m_recvEvent_;										// 接收到的事件
public:
	Channel(const int& thesocket);
	~Channel();
	// 设置接受到的事件状态
	void setRecvEvent(const int& theEvent);
	// 操作事件，如果返回false，连接断开可以删除
	//			 如果返回true   表示还在连接中
	bool handleEvent(const int& epollfd);
	// 回调函数
	void setCallBackFunction(IChannelCallBack* callBack);
	// 获取套接字
	int get_Socket();
};

#endif