#ifndef __ICHANNELCALLBACK_H__
#define __ICHANNELCALLBACK_H__

class IChannelCallBack
{
public:
	// 该套接字是否还有效
	virtual bool ChannelCallBack(const int& thesocket) = 0;
	// 返回套接字
	virtual int get_Socket() = 0;
};
#endif