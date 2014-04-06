#ifndef __IACCEPTERCALLBACK_H__
#define __IACCEPTERCALLBACK_H__
#include "stdafx.h"
class IAccepterCallBack
{
public:
	virtual bool newConnectCallBack(const int& thesocket,
								const std::string& ipaddress,
								const int& port) = 0;
};
#endif