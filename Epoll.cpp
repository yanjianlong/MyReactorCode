#include "Epoll.h"
#include "Channel.h"
Epoll::Epoll(const int& max_event)
{
	m_epollfd_ = epoll_create(MAX_EPOLL_EVENT);
	if(m_epollfd_ <= 0)
		std::cout << "error Epoll : epoll_create" << std::endl;
	std::cout << "Epoll create" << std::endl;
	m_channel_map_.clear();

}

Epoll::~Epoll()
{
	if(m_epollfd_ > 0)
		close(m_epollfd_);
	std::cout << "Epoll delete" << std::endl;
	typedef std::map<int, Channel*>::iterator MAP_ITR;
	MAP_ITR begin = m_channel_map_.begin();
	MAP_ITR end = m_channel_map_.end();
	for (; begin != end; begin++)
	{
		delete begin->second;
		begin->second = NULL;
	}

}

void Epoll::DeleteChannelBySocket(const int& socket)
{
	typedef std::map<int, Channel*>::iterator MAP_ITR;
	MAP_ITR begin = m_channel_map_.begin();
	MAP_ITR end = m_channel_map_.end();
	for (; begin != end; begin++)
	{
		if (begin->first == socket)
		{
			delete begin->second;
			begin->second = NULL;
			m_channel_map_.erase(socket);
			break;
		}
	}
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