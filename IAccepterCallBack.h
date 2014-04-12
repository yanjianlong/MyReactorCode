#ifndef __IACCEPTERCALLBACK_H__
#define __IACCEPTERCALLBACK_H__
#include "stdafx.h"
class IAccepterCallBack
{
public:
	// 添加链接
	virtual bool newConnectCallBack(const int& thesocket,
								const std::string& ipaddress,
								const int& port) = 0;
	// 删除链接
	virtual bool DeleteConnectCallBack(const int& thesocket) = 0;
};
#endif