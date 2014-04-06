#include "TcpConnect.h"
TcpConnect::TcpConnect(const int& thesocket,
					const std::string& ipaddress,
					const int& port)
	: m_socket_(thesocket)
	, m_ipAddress_(ipaddress)
	, m_port_(port)
{}

TcpConnect::~TcpConnect()
{
}

bool TcpConnect::ChannelCallBack(const int& thesocket)
{
	char buffer[1024] = {0};
	int readLength = read(thesocket, buffer, 1024);
	if(readLength > 0)
	{
		std::cout << m_ipAddress_ << ":" << m_port_ 
				<< "read string : " << buffer << std::endl;
		write(thesocket, buffer, readLength + 1);
		std::cout << "write to " << m_ipAddress_ << ":" << m_port_ 
				 << " string : " << buffer << std::endl; 
		return true;
	}
	else
	{
		std::cout << m_ipAddress_ << ":" << m_port_ << " close。" << std::endl;
	}
	return false;
}

bool TcpConnect::Run(const int& epollfd, const int& thesocket)
{
	Channel* pCurChannel = new Channel(thesocket);
	pCurChannel->setCallBackFunction(this);
	return pCurChannel->enableEvent(epollfd, EPOLLIN | EPOLLET);
}
 int TcpConnect::get_Socket()
 {
 	return m_socket_;
 }