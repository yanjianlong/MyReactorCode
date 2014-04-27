#ifndef __USERSERVER_H__ 
#define __USERSERVER_H__
#include "TcpServer.h"
#include "IServerUserCallBack.h"
#include "IRunCallBack.h"
class UserServer
	: public IServerUserCallBack
	, public IRunCallBack
{
private:
	TcpServer* m_UserServer_;
	// 数据分析和获取需要的数据
	void DoAnalyseMessage(const std::string& recvData, 
						std::string& sendData);

	// 增加定时器
	std::list<int64_t> m_TimeFdList_;
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
	void AfterConnect(std::string& sendData, int64_t& theTimeFd);
	// 发送完成
	void CloseConnect(std::string& sendData, const int64_t& theTimeFd);

	// 运行
	void RunCallBack(void* param);
};
#endif