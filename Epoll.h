#ifndef __EPOLL_H__
#define __EPOLL_H__
#include "Channel.h"
class Epoll
{
private:
	Epoll();
	~Epoll();
	int m_epollfd_;
	epoll_event m_epollEvents_[MAX_EPOLL_EVENT];
	static Epoll* m_Instance_;
	// 删除
	class DeleteEpoll
	{
	public:
		DeleteEpoll(){}
		~DeleteEpoll()
		{
			if(m_Instance_)
				delete m_Instance_;
			m_Instance_ = NULL;
		}
	};
	static DeleteEpoll m_deleteEpoll_;
	
public:
	// 获取实例
	static Epoll* GetInstance();

	// 添加监听事件 fd
	bool AddEpollEvent(Channel* pChannel, const int& waiteEvent);
	// 改变监听事件 fd
	bool ModifyEpollEvent(Channel* pChannel, const int& waiteEvent);
	// 删除监听事件
	bool DeleteEpollEvent(Channel* pChannel, const int& waiteEvent);
	// 等待事件
	int WaiteEpollEvent(std::vector<Channel*>& returnChannelVector);
	int get_EpollFD();
};

#endif