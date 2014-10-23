#include "TcpServer.h"
TcpServer::TcpServer(const std::string& ipAddress, 
				const int& port, const bool& block, const int& max_event)
	: m_Accepter_(NULL)
	, m_loop_(NULL)
	, m_epoll_(NULL)
	, m_UserServerCallBack_(NULL)
{
	std::cout << "TcpServer create" << std::endl;

	Init(ipAddress, port, block, max_event);
}
// TcpServer::TcpServer()
// 	: m_Accepter_(NULL)
// 	, m_loop_(NULL)
//	, m_UserServerCallBack_(NULL)
// {}
TcpServer::~TcpServer()
{
	if(m_Accepter_ != NULL)
		delete m_Accepter_;
	m_Accepter_ = NULL;

	if(m_epoll_ != NULL)
		delete m_epoll_;
	m_epoll_ = NULL;

	if(m_loop_ != NULL)
		delete m_loop_;
	m_loop_ = NULL;

	

	std::map<int, TcpConnect*>::iterator theBegin = m_MapTcpConnect_.begin();
	std::map<int, TcpConnect*>::iterator theEnd = m_MapTcpConnect_.end();
	while(theBegin != theEnd)
	{
		close(theBegin->first);
		delete theBegin->second;
		theBegin->second = NULL;
		theBegin++;
	}
	m_MapTcpConnect_.clear();
	std::cout << "TcpServer delete" << std::endl;

}
void TcpServer::Init(const std::string& ipAddress, 
				const int& port, const bool& block, const int& max_event)
{
	if(m_Accepter_ != NULL)
		delete m_Accepter_;
	m_Accepter_ = NULL;
	m_Accepter_ = new Accepter(ipAddress, port, block);
	
	if(m_loop_ != NULL)
		delete m_loop_;
	m_loop_ = NULL;
	m_loop_ = new EventLoop();

	if(m_epoll_ != NULL)
		delete m_epoll_;
	m_epoll_ = new Epoll(max_event);
}

// void TcpServer::InitServer(const std::string& ipAddress, 
// 				const int& port, const bool& block)
// {
// 	Init(ipAddress, port, block);
// }

bool TcpServer::newConnectCallBack(const int& thesocket,
								const std::string& ipaddress,
								const int& port)
{
	// 每当TcpConnect 关闭连接的时候，这个没有删除
	TcpConnect* pTcpConnect = new TcpConnect(thesocket, ipaddress, port);
	pTcpConnect->set_ServerCallBack(m_UserServerCallBack_);
	if(pTcpConnect->Run(thesocket, m_epoll_))
	{
		pTcpConnect->handleConnnectCallBack();
		m_MapTcpConnect_[thesocket] = pTcpConnect;
	}
	else
	{
		delete pTcpConnect;
		pTcpConnect = NULL;
		std::cout << "error TcpServer : newConnectCallBack" << std::endl;
		return false;
	}
	return true;
}

void TcpServer::Start()
{
	m_Accepter_->set_CallBackFunction(this);
	if(m_Accepter_->Run(m_epoll_->get_EpollFD(), m_epoll_))
	{
		m_loop_->set_CallBack(this);
		m_loop_->Loop(m_epoll_);
	}
}

bool TcpServer::DeleteConnectCallBack(const int& thesocket)
{
	if(thesocket == m_Accepter_->get_Socket())
	{
		std::cout << "server socket close" << std::endl;
		m_loop_->CloseEventLoop();
		return true;
	}
	std::map<int, TcpConnect*>::iterator theFind = m_MapTcpConnect_.find(thesocket);
	if(theFind != m_MapTcpConnect_.end())
	{
		close(theFind->first);;
		delete theFind->second;
		theFind->second = NULL;
		std::cout << "delete socket " << theFind->first << std::endl;
		m_MapTcpConnect_.erase(theFind);
	}
	return false;
}

void TcpServer::set_ServerCallBack(IServerUserCallBack* theCallBack)
{
	m_UserServerCallBack_ = theCallBack;
}