#ifndef __ICHANNELCALLBACK_H__
#define __ICHANNELCALLBACK_H__

class IChannelCallBack
{
public:
	// 接收数据是否还有效
	virtual bool RecvDataCallBack(const int& thesocket) = 0;
	
	// 发送数据
	virtual bool SendDataCallBack(const int& thesocket) = 0;
	// 返回套接字
	virtual int get_Socket() = 0;
};
#endif