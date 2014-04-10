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
		std::string SendString = "HTTP/1.1 200 OK\r\nServer: 请叫我捡龙眼\r\n"
								"Connection:close\r\n\r\n"
								"<html>"
									"<head><title>wc is rubbish</title></head>"
									"<body><font size=+4>justtest</font></body>"
								"</html>";
		write(thesocket, SendString.c_str(), SendString.length() + 1);
		std::cout << m_ipAddress_ << ":" << m_port_ << " close。" << std::endl;
		return false;		// 关闭套接字
	}
	else
	{
		std::cout << m_ipAddress_ << ":" << m_port_ << " close。" << std::endl;
	}
	return false;
}

bool TcpConnect::Run(const int& thesocket)
{
	Channel* pCurChannel = new Channel(thesocket);
	pCurChannel->setCallBackFunction(this);
	return Epoll::GetInstance()->AddEpollEvent(pCurChannel, EPOLLIN | EPOLLET);
}
 int TcpConnect::get_Socket()
 {
 	return m_socket_;
 }