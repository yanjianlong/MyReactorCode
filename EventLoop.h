#ifndef __EVENTLOOP_H__
#define __EVENTLOOP_H__
#include "Epoll.h"
#include "IAccepterCallBack.h"
class EventLoop 
{
private:
	bool m_Quit_;
	IAccepterCallBack* m_deleteConnect_;
public:
	EventLoop();
	~EventLoop();
	// 事件循环等待
	void Loop(Epoll* epoll_point);

	// 回调
	void set_CallBack(IAccepterCallBack* theCallBack);

	// 关闭
	void CloseEventLoop();
};

#endif