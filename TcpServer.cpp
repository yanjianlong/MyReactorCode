#include "TcpServer.h"
TcpServer::TcpServer(const std::string& ipAddress, 
				const int& port, const bool& block)
	: m_Accepter_(NULL)
	, m_EpollFd_(-1)
{
	m_Accepter_ = new Accepter(ipAddress, port, block);
}

TcpServer::~TcpServer()
{
	if(m_Accepter_ != NULL)
		delete m_Accepter_;
	m_Accepter_ = NULL;
	if(m_EpollFd_ > 0)
		close(m_EpollFd_);
	m_EpollFd_ = -1;
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
	TcpConnect* pTcpConnect = new TcpConnect(thesocket, ipaddress, port);
	if(pTcpConnect->Run(m_EpollFd_, thesocket))
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
	m_EpollFd_ = epoll_create(MAX_EPOLL_EVENT);
	if(m_EpollFd_ <= 0)
	{
		std::cout << "error TcpServer : epoll_create" << std::endl;
		return ;
	}
	// create the accepter
	if(m_Accepter_ == NULL)
	{
		std::cout << "error TcpServer : Accepter()" << std::endl;
		return ;
	}
	m_Accepter_->set_CallBackFunction(this);
	if(!m_Accepter_->Run(m_EpollFd_))
	{
		std::cout << "error TcpServer : Accepter.Run()" << std::endl;
		return ;
	}
	// 事件
	epoll_event myEvents[MAX_EPOLL_EVENT];
	while(true)
	{
		int waiteNumber = epoll_wait(m_EpollFd_, myEvents, 
								MAX_EPOLL_EVENT - 1, -1);
		if(waiteNumber != -1)
		{
			for(int i = 0; i < waiteNumber; i++)
			{
				//取出隐藏的
				Channel* pCurrentChanel = (Channel*)(myEvents[i].data.ptr);
				// 回调函数
				pCurrentChanel->setRecvEvent(myEvents[i].events); 
				bool theConnectState = pCurrentChanel->handleEvent(m_EpollFd_);
				if(!theConnectState)
				{
					int theCurSocket = pCurrentChanel->get_Socket();
					//维护客户端连接套接字列表
					delete pCurrentChanel;
					// 服务器套接字关闭
					if(theCurSocket == m_Accepter_->get_Socket())
					{
						std::cout << "server socket close" << std::endl;
						return ;
					}
					else	// 客户端套接字关闭
					{
						std::map<int, TcpConnect*>::iterator theFind = m_MapTcpConnect_.find(theCurSocket);
						if(theFind != m_MapTcpConnect_.end())
						{
							close(theFind->first);;
							delete theFind->second;
							m_MapTcpConnect_.erase(theFind);
						}
					}
				}
			}
		}
		else
		{
			std::cout << "error TcpServer : epoll_wait" << std::endl;
		}

	}
}