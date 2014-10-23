#ifndef __EPOLL_H__
#define __EPOLL_H__
#include "Channel.h"
class Epoll
{
private:
	int m_epollfd_;
	epoll_event m_epollEvents_[MAX_EPOLL_EVENT];
	std::map<int, Channel*> m_channel_map_;
	
public:
	Epoll(const int& max_event);
	~Epoll();
	// 添加监听事件 fd
	bool AddEpollEvent(Channel* pChannel, const int& waiteEvent);
	int WaiteEpollEvent(std::vector<Channel*>& returnChannelVector);
	int get_EpollFD();
	void DeleteChannelBySocket(const int& socket);
};

#endif