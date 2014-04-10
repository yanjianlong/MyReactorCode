#ifndef __EVENTLOOP_H__
#define __EVENTLOOP_H__
#include "Epoll.h"
#include "IEpollEventCallBack.h"
class EventLoop 
{
private:
	bool m_Quit_;
	//EpollEventCallBack m_callback_;
public:
	EventLoop();
	~EventLoop();
	// 事件循环等待
	void Loop();
	// 添加事件监听
	bool AddEventToEpoll(Channel* pChannel, 
						const int& curEvent);
	// 获取ID
	int get_EpollFD();

	// 回调
	void set_CallBack(EpollEventCallBack theCallBack);

	// 关闭
	void CloseEventLoop();
};

#endif