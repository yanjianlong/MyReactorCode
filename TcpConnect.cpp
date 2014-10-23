#include "TcpConnect.h"
TcpConnect::TcpConnect(const int& thesocket,
					const std::string& ipaddress,
					const int& port)
	: m_socket_(thesocket)
	, m_ipAddress_(ipaddress)
	, m_port_(port)
	, m_UserServerCallBack_(NULL)
{
	std::cout << "tcpconnect create" << std::endl;

}

TcpConnect::~TcpConnect()
{
	std::cout << "tcpconnet delete" << std::endl;

}

bool TcpConnect::ChannelCallBack(const int& thesocket)
{
	char buffer[1024] = {0};
	int readLength = read(thesocket, buffer, 1024);
	if(readLength > 0)
	{
		handleSendMessageCallBack(thesocket, buffer);
		return false;		// 关闭套接字
	}
	else
	{
		std::cout << m_ipAddress_ << ":" << m_port_ << " close。" << std::endl;
	}
	return false;
}

bool TcpConnect::Run(const int& thesocket, Epoll* epoll_point)
{
	Channel* pCurChannel = new Channel(thesocket);
	pCurChannel->setCallBackFunction(this);
	return epoll_point->AddEpollEvent(pCurChannel, EPOLLIN | EPOLLET);
}
int TcpConnect::get_Socket()
{
	return m_socket_;
}

void TcpConnect::set_ServerCallBack(IServerUserCallBack* theCallBack)
{
	m_UserServerCallBack_ = theCallBack;
}

void TcpConnect::handleConnnectCallBack()
{
	if(m_UserServerCallBack_ != NULL)
	{
		std::string sendData = "";
		m_UserServerCallBack_->AfterConnect(sendData);
	}
	else
	{
		std::cout << "error TcpConnect : handleConnnectCallBack" << std::endl;
	}
}

void TcpConnect::handleSendMessageCallBack(const int& thesocket,
						const std::string& recvData)
{
	std::cout << m_ipAddress_ << ":" << m_port_ 
				<< "read string : " << recvData << std::endl;
	std::string SendString = "HTTP/1.1 200 OK\r\nServer: my name is jianlongyan\r\n"
							"Connection:close\r\n\r\n"
							"<html>"
								"<head><title>wc is rubbish</title></head>"
								"<body><font size=+4>justtest</font></body>"
							"</html>";
	if(m_UserServerCallBack_ != NULL)
	{
		// 回调发送事件
		m_UserServerCallBack_->SendMessage(recvData, SendString);
		write(thesocket, SendString.c_str(), SendString.length() + 1);
	}
	else
	{
		std::cout << "error TcpConnect : handleSendMessageCallBack" << std::endl;
	}
	std::cout << m_ipAddress_ << ":" << m_port_ << " close。" << std::endl;
}