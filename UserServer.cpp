#include "UserServer.h"
UserServer::UserServer(const std::string& ipAddress, 
				const int& port, const bool& block)
	: m_UserServer_(NULL)
{
	m_UserServer_ = new TcpServer(ipAddress, port, block);
}

UserServer::~UserServer()
{
	if(m_UserServer_ != NULL)
		delete m_UserServer_;
	m_UserServer_ = NULL;
}

void UserServer::StartServer()
{
	m_UserServer_->set_ServerCallBack(this);
	m_UserServer_->Start();
}

void UserServer::DoAnalyseMessage(const std::string& recvData, 
								std::string& sendData)
{
	// 数据处理
}
void UserServer::SendMessage(const std::string& recvData, 
					std::string& sendData)
{
	DoAnalyseMessage(recvData, sendData);
	std::cout << "UserServer handle sendMessage" << std::endl;
}

void UserServer::AfterConnect(std::string& sendData)
{
	// do your things
	std::cout << "UserServer handle Connect" << std::endl;
}