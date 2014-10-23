#include "EventLoop.h"
EventLoop::EventLoop()
	: m_Quit_(false)
	, m_deleteConnect_(NULL)
{
	std::cout << "Eventloop create" << std::endl;

}

EventLoop::~EventLoop()
{
	std::cout << "EventLoop delete" << std::endl;

}

void EventLoop::Loop(Epoll* epoll_point)
{
	while(!m_Quit_)
	{
		std::vector<Channel*> waiteChannelVector;
		epoll_point->WaiteEpollEvent(waiteChannelVector);
		std::vector<Channel*>::iterator theBegin = waiteChannelVector.begin();
		std::vector<Channel*>::iterator theEnd = waiteChannelVector.end();
		for(; theBegin != theEnd; theBegin++)
		{
			if((*theBegin)->handleEvent(epoll_point->get_EpollFD()))
			{}
			else
			{
				int socketfd = (*theBegin)->get_Socket();
				if(m_deleteConnect_)
					m_deleteConnect_->DeleteConnectCallBack(socketfd);
				close(socketfd);
				epoll_point->DeleteChannelBySocket(socketfd);
			}
		}
	}
}

void EventLoop::set_CallBack(IAccepterCallBack* theCallBack)
{
	m_deleteConnect_ = theCallBack;
}

void EventLoop::CloseEventLoop()
{
	m_Quit_ = true;
}