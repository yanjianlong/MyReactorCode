#include "TcpConnect.h"
TcpConnect::TcpConnect(const int& thesocket,
					const std::string& ipaddress,
					const int& port)
	: m_socket_(thesocket)
	, m_ipAddress_(ipaddress)
	, m_port_(port)
	, m_UserServerCallBack_(NULL)
	, m_recvBuffer_("")
	, m_sendBuffer_("")
	, m_bufferSzie_(1024)
{}

TcpConnect::~TcpConnect()
{
}

bool TcpConnect::RecvDataCallBack(const int& thesocket)
{
	char buffer[m_bufferSzie_ + 1];
	int readLength = read(thesocket, buffer, m_bufferSzie_);
	buffer[readLength] = '\0';
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

bool TcpConnect::SendDataCallBack(const int& thesocket)
{
	return true;
}

void TcpConnect::handleSendMessageCallBack(const int& thesocket,
						const std::string& recvData)
{
	std::cout << m_ipAddress_ << ":" << m_port_ 
				<< "read string : " << recvData << std::endl;
	m_sendBuffer_= "HTTP/1.1 200 OK\r\nServer: 请叫我捡龙眼\r\n"
				"Connection:close\r\n\r\n"
				"<html>"
					"<head><title>wc is rubbish</title></head>"
					"<body><font size=+4>justtest</font></body>"
				"</html>";
	if(m_UserServerCallBack_ != NULL)
	{
		// 回调发送事件 
		m_UserServerCallBack_->SendMessage(recvData, m_sendBuffer_);		// 构建返回消息
		sendBuffer(thesocket);
	}
	else
	{
		std::cout << "error TcpConnect : handleSendMessageCallBack" << std::endl;
	}
	//std::cout << m_ipAddress_ << ":" << m_port_ << " close。" << std::endl;
}

bool TcpConnect::sendBuffer(const int& thesocket)
{
	const int max_send_buffer = 20;
	while(m_sendBuffer_.length() > 0)
	{
		if(m_sendBuffer_.length() > max_send_buffer)
		{
			std::string theSend = m_sendBuffer_.substr(0, max_send_buffer);
			int sendlength = write(thesocket, theSend.c_str(), theSend.length());
			m_sendBuffer_ = m_sendBuffer_.substr(sendlength, m_sendBuffer_.length());
		}
		else
			write(thesocket, m_sendBuffer_.c_str(), m_sendBuffer_.length());
	}
	return true;
}