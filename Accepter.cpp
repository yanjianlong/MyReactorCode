#include "Accepter.h"
Accepter::Accepter(const std::string& ipAddress, 
		const int& port, const bool& bNonlock)
	:  m_TcpServerCallBack_(NULL)
	, m_ipAddress_(ipAddress)
	, m_port_(port)
	, m_bNonBlock_(true)
{
}
Accepter::~Accepter()
{}
bool Accepter::Run(const int& epollfd)
{
	if(!m_serverSocket_.createSocket(m_bNonBlock_))
	{
		std::cout << "error Accepter : createSocket" << std::endl;
		return false;
	}
	if(!m_serverSocket_.dobind(m_ipAddress_, m_port_))
	{
		std::cout << "error Accepter : dobind" << std::endl;
		return false;
	}
	if(!m_serverSocket_.dolisten(MAX_EPOLL_EVENT - 1))
	{
		std::cout << "error Accepter : dolisten" << std::endl;
		return false;
	}
	Channel* pAccepterChannel = new Channel(m_serverSocket_.get_Socket());
	pAccepterChannel->setCallBackFunction(this);
	if(Epoll::GetInstance()->AddEpollEvent(pAccepterChannel, EPOLLIN | EPOLLET))
		return true;
	else 
	{
		std::cout << "ERROR Accepter : enableEvent()" << std::endl;
		delete pAccepterChannel;
		return false;
	}
}

bool Accepter::ChannelCallBack(const int& thesocket)
{
	// 连接
	if(thesocket == m_serverSocket_.get_Socket())
	{
		sockaddr_in clientAddr;
		socklen_t theLengthAddr = sizeof(clientAddr);
		memset(&clientAddr, 0, sizeof(clientAddr));
		int clientSocket = accept(m_serverSocket_.get_Socket(), (sockaddr*)&clientAddr, &theLengthAddr);
		if(clientSocket > 0)
		{
			std::string theIpAddress = inet_ntoa(clientAddr.sin_addr);
			int port = ntohs(clientAddr.sin_port);
			std::cout << "new connection form " << theIpAddress
						<< ":" << port
						<< "(" << clientSocket << ")" << std::endl;
			if(m_TcpServerCallBack_)
				m_TcpServerCallBack_->newConnectCallBack(clientSocket, theIpAddress, port);
			else
				std::cout << "error Accepter : ChannelCallBack" << std::endl;
		}
		return true;
	}
	else
	{
		std::cout << "error : Accepter ChannelCallBack" << std::endl;
	}
	return false;
}

int Accepter::get_Socket()
{
	return m_serverSocket_.get_Socket();
}

void Accepter::set_CallBackFunction(IAccepterCallBack* theCallBack)
{
	m_TcpServerCallBack_ = theCallBack;
}