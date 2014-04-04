#include "TcpServer.h"
TcpServer::TcpServer(const std::string& ipAddress, 
				const int& port, const bool& block)
	: m_ipAddress_(ipAddress)
	, m_port_(port)
	, m_bBlock_(true)
	, m_EpollFd_(-1)
{
}

TcpServer::~TcpServer()
{}

/*
	存在问题
	Channel* 对象内存泄漏
 */
bool TcpServer::CallBackFunction(const int& thesocket)
{
	// 连接
	if(thesocket == m_MySocket_.get_Socket())
	{
		sockaddr_in clientAddr;
		socklen_t theLengthAddr = sizeof(clientAddr);
		memset(&clientAddr, 0, sizeof(clientAddr));
		int clientSocket = accept(m_MySocket_.get_Socket(), (sockaddr*)&clientAddr, &theLengthAddr);
		if(clientSocket > 0)
		{
			std::cout << "new connection form " << inet_ntoa(clientAddr.sin_addr)
						<< ":" << ntohs(clientAddr.sin_port) 
						<< "(" << clientSocket << ")" << std::endl;
			// 注册客户端套接字事件
			Channel* pClientChanel = new Channel(clientSocket);
			pClientChanel->setCallBackFunction(this);
			pClientChanel->enableEvent(m_EpollFd_, EPOLLIN | EPOLLET);
		}
	}
	// recv / send
	else
	{
		const int MAX_BUFFER_LENGTH = 1024;
		char theBuffer[MAX_BUFFER_LENGTH] = {0};
		int readNumber = read(thesocket, theBuffer, MAX_BUFFER_LENGTH - 1);
		if(readNumber > 0)
		{
			std::cout << "(" << thesocket << ") read " << readNumber << "chars : " 
						<< theBuffer << std::endl;
			int writeNumber = write(thesocket, theBuffer, readNumber + 1);
			std::cout << "(" << thesocket << ") write:" << theBuffer << std::endl;
		}
		else
		{
			close(thesocket);
			std::cout << "(" << thesocket << ") close; " << std::endl;
			return false;
		}
		
	}
	return true;
}

void TcpServer::Start()
{
	if(!m_MySocket_.createSocket(m_bBlock_))
		return ;
	if(!m_MySocket_.dobind(m_ipAddress_, m_port_))
		return ;
	if(!m_MySocket_.dolisten(MAX_EPOLL_EVENT - 1))
		return ;
	m_EpollFd_ = epoll_create(MAX_EPOLL_EVENT);
	if(m_EpollFd_ <= 0)
		return ;
	// 事件
	epoll_event myEvents[MAX_EPOLL_EVENT];
	Channel* theServerChanel = new Channel(m_MySocket_.get_Socket());
	theServerChanel->setCallBackFunction(this);
	// 添加事件
	if (theServerChanel->enableEvent(m_EpollFd_, EPOLLIN | EPOLLET)) 
	{
		while(true)
		{
			//  等待事件发生
			int waitefdnumber = epoll_wait(m_EpollFd_, myEvents, 
											MAX_EPOLL_EVENT, -1);
			if(waitefdnumber != -1)
			{
				// 遍历
				for(int i = 0; i < waitefdnumber; i++)
				{
					// 取出隐藏的
					Channel* pCurrentChanel = (Channel*)(myEvents[i].data.ptr);
					// 回调函数
					pCurrentChanel->setRecvEvent(myEvents[i].events); 
					bool theConnectState = pCurrentChanel->handleEvent(m_EpollFd_);
					if(!theConnectState)
						delete pCurrentChanel;
				}
			}
			else
			{
				std::cout << "epoll_waite error" << std::endl;
			}
		}
	}
	else
		delete theServerChanel;
}