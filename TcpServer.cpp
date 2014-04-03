#include "TcpServer.h"
TcpServer::TcpServer(const std::string& ipAddress, const int& port, const bool& block)
	: m_ipAddress_(ipAddress)
	, m_port_(port)
	, m_bBlock_(true)
	, m_EpollFd_(-1)
{

}

TcpServer::~TcpServer()
{}


void TcpServer::CallBackFunction()
{
	
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
	// accept
    epoll_event  ev;
    epoll_event myEvents[MAX_EPOLL_EVENT];
    ev.events = EPOLLIN | EPOLLET;
    ev.data.fd = m_MySocket_.get_Socket();
    sockaddr_in clientAddr;
    int sizeofAddr = sizeof(clientAddr);
    const int MAX_BUFFER_LENGTH = 1024;
    char buffer[MAX_BUFFER_LENGTH] = {0};
    // 添加事件
    if (epoll_ctl(m_EpollFd_, EPOLL_CTL_ADD, m_MySocket_.get_Socket(), &ev) == 0) 
    {
         while(true)
         {
              //  等待事件发生
              int waitefdnumber = epoll_wait(m_EpollFd_, myEvents, MAX_EPOLL_EVENT, -1);
              if(waitefdnumber != -1)
              {
                   // 遍历
                   for(int i = 0; i < waitefdnumber; i++)
                   {
                        // connect
                        int theCurFd = myEvents[i].data.fd;
                        if(theCurFd == m_MySocket_.get_Socket())
                        {
                             int connectfd = accept(m_MySocket_.get_Socket(), 
                                                      (sockaddr*)&clientAddr,
                                                      (socklen_t*)&sizeofAddr);
                             if(connectfd > 0)
                             {
                                  std::cout << inet_ntoa(clientAddr.sin_addr)
                                  << " : " << clientAddr.sin_port << " connect "
                                  << std::endl; 
                             }
                             ev.events = EPOLLIN | EPOLLET;
                             ev.data.fd = connectfd;
                             if (epoll_ctl(m_EpollFd_, EPOLL_CTL_ADD, connectfd, &ev) == 0) 
                             {}
                        }
                        else
                        {
                             int nread = read(theCurFd, buffer, MAX_BUFFER_LENGTH);
                             if(nread == 0)
                             {
                                  close(theCurFd);
                                  std::cout << "close " << std::endl;
                             }
                             std::cout << "receive : " << buffer << std::endl;
                             write(theCurFd, buffer, nread);
                        }
                   }
              }
         }
    }
}