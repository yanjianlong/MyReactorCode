#include "UserServer.h"
UserServer::UserServer(const std::string& ipAddress, 
				const int& port, const bool& block, const int& max_event)
	: m_UserServer_(NULL)
{
	std::cout << "Userserver create" << std::endl;

	m_UserServer_ = new TcpServer(ipAddress, port, block, max_event);
}

UserServer::~UserServer()
{
	if(m_UserServer_ != NULL)
		delete m_UserServer_;
	m_UserServer_ = NULL;
	std::cout << "Userserver delete" << std::endl;

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