#ifndef __USERSERVER_H__ 
#define __USERSERVER_H__
#include "TcpServer.h"
#include "IServerUserCallBack.h"
class UserServer
	: public IServerUserCallBack
{
private:
	TcpServer* m_UserServer_;
	// 数据分析和获取需要的数据
	void DoAnalyseMessage(const std::string& recvData, 
						std::string& sendData);
public:
	// 初始化用户服务器
	UserServer(const std::string& ipAddress, 
			const int& port, const bool& block);
	~UserServer();
	// start the server
	void StartServer();
	// 发送信息
	void SendMessage(const std::string& recvData, 
					std::string& sendData);
	// 连接建立
	void AfterConnect(std::string& sendData);
};
#endif