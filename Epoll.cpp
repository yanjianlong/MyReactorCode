#include "Epoll.h"
#include "Channel.h"
Epoll* Epoll::m_Instance_ = NULL;
Epoll* Epoll::GetInstance()
{
	if(m_Instance_ == NULL)
	{
		// 加锁
		if(m_Instance_ == NULL)
			m_Instance_ = new Epoll();
		// 解锁
	}
	return m_Instance_;
}

Epoll::Epoll()
{
	m_epollfd_ = epoll_create(MAX_EPOLL_EVENT);
	if(m_epollfd_ <= 0)
		std::cout << "error Epoll : epoll_create" << std::endl;
}

Epoll::~Epoll()
{
	if(m_epollfd_ > 0)
		close(m_epollfd_);
}

int Epoll::WaiteEpollEvent(std::vector<Channel*>& returnChannelVector)
{
	int numberFds = epoll_wait(m_epollfd_, m_epollEvents_, 
								MAX_EPOLL_EVENT, -1);
	returnChannelVector.resize(numberFds);
	returnChannelVector.clear();
	if(numberFds < 0)
	{
		std::cout << "error Epoll : epoll_waite" << std::endl;
		return 0;
	}
	for(int i = 0; i < numberFds; i++)
	{
		Channel* pChannel = (Channel*)(m_epollEvents_[i].data.ptr);
		pChannel->setRecvEvent(m_epollEvents_[i].events);
		returnChannelVector.push_back(pChannel);
	}
	return numberFds;
}

bool Epoll::AddEpollEvent(Channel* pChannel, const int& waiteEvent)
{
	epoll_event theCurEvent;
	theCurEvent.data.ptr = pChannel;
	theCurEvent.events = waiteEvent;
	if(0 == epoll_ctl(m_epollfd_, EPOLL_CTL_ADD, pChannel->get_Socket(), &theCurEvent))
		return true;
	return false;
}

int Epoll::get_EpollFD()
{
	return m_epollfd_;
}

bool Epoll::ModifyEpollEvent(Channel* pChannel, const int& waiteEvent)
{
	epoll_event ev;
    ev.data.ptr = pChannel;
    ev.events = waiteEvent;
    epoll_ctl(m_epollfd_, EPOLL_CTL_MOD, pChannel->get_Socket(), &ev);
	return true;
}

bool Epoll::DeleteEpollEvent(Channel* pChannel, const int& waiteEvent)
{
	epoll_ctl(m_epollfd_, EPOLL_CTL_DEL, pChannel->get_Socket(), NULL);
	return true;
}