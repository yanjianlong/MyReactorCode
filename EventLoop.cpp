#include "EventLoop.h"
EventLoop::EventLoop()
	: m_Quit_(false)
	, m_deleteConnect_(NULL)
	, m_pTimeQueue_(NULL)
{
	m_timefdCallBackClass_.clear();
	m_pTimeQueue_ = new TimeQueue();
	if(m_pTimeQueue_)
		m_pTimeQueue_->Run(m_pTimeQueue_->get_Socket());
}

EventLoop::~EventLoop()
{
	delete m_pTimeQueue_;
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
				Epoll::GetInstance()->DeleteEpollEvent(*theBegin, 0);
				int socketfd = (*theBegin)->get_Socket();
				if(m_deleteConnect_)
					m_deleteConnect_->DeleteConnectCallBack(socketfd);
				close(socketfd);
				delete (*theBegin);
				*theBegin = NULL;
			}
		}
		DoPendingFunctions();
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

void EventLoop::DoPendingFunctions()
{
	std::vector<RunClass> tempCallBack;
	tempCallBack.swap(m_timefdCallBackClass_);
	std::vector<RunClass>::iterator theBegin = tempCallBack.begin();
	std::vector<RunClass>::iterator theEnd = tempCallBack.end();
	for(; theBegin != theEnd; theBegin++)
	{
		theBegin->Run();
	}
}

// 定点调用
int64_t EventLoop::runAt(const double& theTime, IRunCallBack* theCallBack)
{
	// 创建定时任务
	if(m_pTimeQueue_)
		 return m_pTimeQueue_->AddTimerRuner(theCallBack, theTime, 0);
	return 0;
}
// 等待一段时间后调用
int64_t EventLoop::runAfter(const double& theTime, IRunCallBack* theCallBack)
{
	if(m_pTimeQueue_)
		 return m_pTimeQueue_->AddTimerRuner(theCallBack, theTime, 0);
	return 0;
}
// 每隔多少时间调用
int64_t EventLoop::runEvery(const double& theTime, IRunCallBack* theCallBack)
{	
	if(m_pTimeQueue_)
		 return m_pTimeQueue_->AddTimerRuner(theCallBack, theTime, theTime);
	return 0;
}
// 删除定时器
void EventLoop::cancelTimer(const int64_t& timefd)
{
	m_pTimeQueue_->CancelTimer(timefd);
}