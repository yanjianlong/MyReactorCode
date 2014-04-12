#include "TcpServer.h"
TcpServer::TcpServer(const std::string& ipAddress, 
				const int& port, const bool& block)
	: m_Accepter_(NULL)
	, m_loop_(NULL)
	//, m_CallBack_(NULL)
{
	m_Accepter_ = new Accepter(ipAddress, port, block);
	m_loop_ = new EventLoop();
	//m_CallBack_ = (EpollEventCallBack)(&TcpServer::DeleteConnect);
}

TcpServer::~TcpServer()
{
	if(m_Accepter_ != NULL)
		delete m_Accepter_;
	m_Accepter_ = NULL;

	if(m_loop_ != NULL)
		delete m_loop_;
	m_loop_ = NULL;

	std::map<int, TcpConnect*>::iterator theBegin = m_MapTcpConnect_.begin();
	std::map<int, TcpConnect*>::iterator theEnd = m_MapTcpConnect_.end();
	while(theBegin != theEnd)
	{
		close(theBegin->first);
		delete theBegin->second;
		theBegin++;
	}
	m_MapTcpConnect_.clear();
}

bool TcpServer::newConnectCallBack(const int& thesocket,
								const std::string& ipaddress,
								const int& port)
{
	// 每当TcpConnect 关闭连接的时候，这个没有删除
	TcpConnect* pTcpConnect = new TcpConnect(thesocket, ipaddress, port);
	if(pTcpConnect->Run(thesocket))
	{
		m_MapTcpConnect_[thesocket] = pTcpConnect;
	}
	else
	{
		delete pTcpConnect;
		std::cout << "error TcpServer : newConnectCallBack" << std::endl;
		return false;
	}
	return true;
}

void TcpServer::Start()
{
	m_Accepter_->set_CallBackFunction(this);
	m_Accepter_->Run(m_loop_->get_EpollFD());
	m_loop_->set_CallBack(this);
	m_loop_->Loop();
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
		std::cout << "delete socket " << theFind->first << std::endl;
		m_MapTcpConnect_.erase(theFind);
	}
	return false;
}