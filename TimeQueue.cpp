#include "TimeQueue.h"
#include "Epoll.h"
TimeQueue::TimeQueue()
	: m_timefd_(-1)
	, kMicroSecondsPerSecond(1000000)
{
	m_timefd_ = timerfd_create(CLOCK_MONOTONIC,
            TFD_NONBLOCK | TFD_CLOEXEC);
	if(m_timefd_ < 0)
		std::cout << "error  TimeQueue : timerfd_create" << std::endl;
	m_TimerRuner_.clear();
}

TimeQueue::~TimeQueue()
{
	if(m_timefd_ != -1)
		close(m_timefd_);
}

bool TimeQueue::Run(const int& thesocket)
{
	Channel* theChannel = new Channel(thesocket);
	if(theChannel == NULL)
		return false;
	theChannel->setCallBackFunction(this);
	if(Epoll::GetInstance()->AddEpollEvent(theChannel, EPOLLET | EPOLLIN))
	{
		return true;
	}
	else
	{
		delete theChannel;
		theChannel = NULL;
		return false;
	}
}

bool TimeQueue::RecvDataCallBack(const int& thesocket)
{
	// 遍历时间回调进行
	uint64_t curtime;
	size_t n = read(thesocket, &curtime, sizeof(curtime));
	curtime = nowMicroSeconds();
	std::cout << "curtime : " << curtime << std::endl;
	/*根据当前系统时间获取需要执行的时间队列*/
	std::map<int64_t, TimeRuner> theCurRuner;
	{
		std::map<int64_t, TimeRuner>::iterator theEnd 
						= m_TimerRuner_.lower_bound(curtime);
		// 清理已经处理的额
		std::map<int64_t, TimeRuner>::iterator theBegin
					= m_TimerRuner_.begin();
		if(theEnd != m_TimerRuner_.end())
		{
			for(; theBegin != theEnd; theBegin++)
			{
				theCurRuner[theBegin->first] = theBegin->second;
			}
			theCurRuner[theEnd->first] = theEnd->second;
			m_TimerRuner_.erase(m_TimerRuner_.begin(), theEnd);
		}
		else
		{
			m_TimerRuner_.clear();
		}
	}
	{
		/*执行时间队列*/
		std::map<int64_t, TimeRuner>::iterator theBegin
					= theCurRuner.begin();
		std::map<int64_t, TimeRuner>::iterator theEnd
					= theCurRuner.end();
		for(; theBegin != theEnd; theBegin++)
		{
			theBegin->second.Run();
		}
	}
	{
		// next time
	}	
	return true;
}
	

bool TimeQueue::SendDataCallBack(const int& thesocket)
{
	return true;
}

	// 返回套接字
int TimeQueue::get_Socket()
{
	return m_timefd_;
}

int64_t TimeQueue::nowMicroSeconds()
{
	struct timeval tv;
	gettimeofday(&tv, NULL);
    return tv.tv_usec;
}

int64_t TimeQueue::AddTimerRuner(IRunCallBack* theCallBack, 
							const int& theNextRunTime, 
							const int& everyTime)
{
	int64_t theNowTime = nowMicroSeconds() + theNextRunTime * kMicroSecondsPerSecond;
	TimeQueue::TimeRuner theRunner(theCallBack, theNowTime, everyTime);
	m_TimerRuner_[theNowTime] = theRunner;
	SetTimeFD(theNowTime);
	return theNowTime;
}

void TimeQueue::SetTimeFD(const int64_t& theTimeNext)
{
    int64_t theDistanceTime = theTimeNext - nowMicroSeconds();
    InitTimerFD(theDistanceTime);
}
void TimeQueue::InitTimerFD(const int64_t& theTimeNext)
{
	struct itimerspec newValue;
    struct itimerspec oldValue;
    bzero(&newValue, sizeof(newValue));
    bzero(&oldValue, sizeof(oldValue));
    int64_t theDistanceTime = theTimeNext;
    theDistanceTime = theDistanceTime > 200 ? theDistanceTime : 200;
    // 秒数
    newValue.it_value.tv_sec = theDistanceTime / kMicroSecondsPerSecond;
    // 
    newValue.it_value.tv_nsec = theDistanceTime % kMicroSecondsPerSecond * 1000;
    int ret = ::timerfd_settime(m_timefd_, 0, &newValue, &oldValue);
    if(ret)
    {
        std::cout << "error TimeQueue : timerfd_settime error" << std::endl;

    }
}
void TimeQueue::CancelTimer(const int64_t& timefd)
{
	// 找到定时器 删除任务
	m_TimerRuner_.erase(timefd);
	std::cout << "TimeQueue m_TimerRuner_ size : " << m_TimerRuner_.size() << std::endl;
}