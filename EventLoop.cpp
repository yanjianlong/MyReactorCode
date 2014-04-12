#include "EventLoop.h"
EventLoop::EventLoop()
	: m_Quit_(false)
	, m_deleteConnect_(NULL)
{
}

EventLoop::~EventLoop()
{
}

void EventLoop::Loop()
{
	while(!m_Quit_)
	{
		std::vector<Channel*> waiteChannelVector;
		Epoll::GetInstance()->WaiteEpollEvent(waiteChannelVector);
		std::vector<Channel*>::iterator theBegin = waiteChannelVector.begin();
		std::vector<Channel*>::iterator theEnd = waiteChannelVector.end();
		for(; theBegin != theEnd; theBegin++)
		{
			if((*theBegin)->handleEvent(Epoll::GetInstance()->get_EpollFD()))
			{}
			else
			{
				int socketfd = (*theBegin)->get_Socket();
				if(m_deleteConnect_)
					m_deleteConnect_->DeleteConnectCallBack(socketfd);
				close(socketfd);
				delete (*theBegin);
				*theBegin = NULL;
			}
		}
	}
}

bool EventLoop::AddEventToEpoll(Channel* pChannel,
						const int& curEvent)
{
	return Epoll::GetInstance()->AddEpollEvent(pChannel, curEvent);
}

int EventLoop::get_EpollFD()
{
	return Epoll::GetInstance()->get_EpollFD();
}

void EventLoop::set_CallBack(IAccepterCallBack* theCallBack)
{
	m_deleteConnect_ = theCallBack;
}

void EventLoop::CloseEventLoop()
{
	m_Quit_ = true;
}