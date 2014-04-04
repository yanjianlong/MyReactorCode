#ifndef __ICHANNELCALLBACK_H__
#define __ICHANNELCALLBACK_H__

class IChannelCallBack
{
public:
	// 该套接字是否还有效
	virtual bool CallBackFunction(const int& thesocket) = 0;
};
#endif