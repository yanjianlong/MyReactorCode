#include "UserServer.h"
UserServer::UserServer(const std::string& ipAddress, 
				const int& port, const bool& block)
	: m_UserServer_(NULL)
{
	m_UserServer_ = new TcpServer(ipAddress, port, block);
	m_TimeFdList_.clear();
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
	// 构造数据
	DoAnalyseMessage(recvData, sendData);
	std::cout << "UserServer handle sendMessage" << std::endl;
	// 发送数据	
}

void UserServer::AfterConnect(std::string& sendData, int64_t& theTimeFd)
{
	// do your things
	std::cout << "UserServer handle Connect" << std::endl;
	// 增加定时器
	theTimeFd = m_UserServer_->m_loop_->runEvery(1, this);
	m_TimeFdList_.push_back(theTimeFd);
}

void UserServer::CloseConnect(std::string& sendData, const int64_t& theTimeFd)
{
	// do your things
	std::cout << "UserServer handle SendMessage success, ready to close ! " << std::endl;
	m_TimeFdList_.remove(theTimeFd);
	std::cout << "m_TimeFdList_ size : " << m_TimeFdList_.size() << std::endl;
	m_UserServer_->m_loop_->cancelTimer(theTimeFd);
}

void UserServer::RunCallBack(void* param)
{
	std::cout << "runing!" << std::endl;
}