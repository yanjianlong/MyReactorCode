#include "mysocket.h"
JianLongYanSocket::JianLongYanSocket()
	: m_Socket_(-1)
{
	std::cout << "JianLongYanSocket JianLongYanSocket" 
			<< std::endl;

}
JianLongYanSocket::~JianLongYanSocket()
{
	if(m_Socket_ != -1)
	{
		close(m_Socket_);
		m_Socket_ = -1;
	}
	std::cout << "JianLongYanSocket ~JianLongYanSocket" 
			<< std::endl;
}

int JianLongYanSocket::get_Socket()
{
	return m_Socket_;	
}

bool JianLongYanSocket::doconnect(const std::string& ipAddress, const int& port)
{
	if(m_Socket_ != -1)
	{
		sockaddr_in serverSocketAddr;
		memset(&serverSocketAddr, 0, sizeof(serverSocketAddr));
		serverSocketAddr.sin_family = AF_INET;
		serverSocketAddr.sin_port = htons(port);
		if(inet_aton(ipAddress.c_str(), &serverSocketAddr.sin_addr))
		{
			if(connect(m_Socket_, (sockaddr*)&serverSocketAddr, sizeof(serverSocketAddr)) == 0)
			{
				return true;
			}
		}
	}
	return false;
}

bool JianLongYanSocket::createSocket(const bool& bNoneBlock)
{
	//socket
	m_Socket_ = socket(AF_INET, SOCK_STREAM, 0);
	if(m_Socket_ != -1)
	{
		if(bNoneBlock)
		{
			// no blocking
			if(-1 == fcntl(m_Socket_, F_SETFL, O_NONBLOCK))
				return false;
		}
		return true;
	}
	return false;
}
bool JianLongYanSocket::dobind(const std::string& ipAddress, const int& port)
{
	if(m_Socket_ == -1)
		return false;
	sockaddr_in serverSocketAddr;
	memset(&serverSocketAddr, 0, sizeof(serverSocketAddr));
	serverSocketAddr.sin_family = AF_INET;
	serverSocketAddr.sin_port = htons(port);
	if(inet_aton(ipAddress.c_str(), &serverSocketAddr.sin_addr))
  		if(0 == bind(m_Socket_, (sockaddr*)&serverSocketAddr, 
			sizeof(serverSocketAddr)))
			return true;
	return false;
}
bool JianLongYanSocket::dolisten(const int& listenNumber)
{
	if(m_Socket_ == -1)
		return false;
	if(0 == listen(m_Socket_, listenNumber))
		return true;
	return false;
}


// void JianLongYanSocket::DoAccept()
// {
// }