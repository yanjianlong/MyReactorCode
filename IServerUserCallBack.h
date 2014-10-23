#ifndef __ISERVERUSERCALLBACK_H__
#define __ISERVERUSERCALLBACK_H__ 
#include "stdafx.h"
class IServerUserCallBack
{
public:
	// 接受数据，发送数据
	virtual void SendMessage(const std::string& recvData, 
							std::string& sendData) = 0;
	// 发送数据
	virtual void AfterConnect(std::string& sendData) = 0;
};

#endif