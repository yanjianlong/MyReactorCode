#ifndef __TIMEQUEUE_H__  
#define __TIMEQUEUE_H__
#include "IChannelCallBack.h"
#include "stdafx.h"
#include <sys/timerfd.h>
#include <inttypes.h>
#include "IRunCallBack.h"
class TimeQueue 
	: public IChannelCallBack
{
public:
	TimeQueue();
	~TimeQueue();

	// 接收数据是否还有效
	bool RecvDataCallBack(const int& thesocket);
	
	// 发送数据
	bool SendDataCallBack(const int& thesocket);

	// 返回套接字
	int get_Socket();

	// 获取当前时间
	int64_t nowMicroSeconds();

	// 描述时间定时器的结构
	class TimeRuner
	{
	public:
		TimeRuner()
		{}
		TimeRuner(IRunCallBack* theCallBack, const int64_t& theNextRunTime, const int& everyTime)
			: m_theCallBack_(theCallBack)
			, m_nextRunTime_(theNextRunTime)
			, m_everyTime_(everyTime)
		{
		}
		~TimeRuner()
		{}
		void Run()
		{
			m_theCallBack_->RunCallBack(NULL);		
		}
	private:
		IRunCallBack* m_theCallBack_;
		int64_t m_nextRunTime_;
		int m_everyTime_;
	};
	// 增加定时功能  
	// 回调  下次执行的时间点  每隔多少时间执行
	int64_t AddTimerRuner(IRunCallBack* theCallBack, 
					const int& theNextRunTime, 
					const int& everyTime);

	/*
		取消定时服务
	 */
	void CancelTimer(const int64_t& timefd);

	// 运行
	bool Run(const int& thesocket);
private:
	int m_timefd_;
	// 任务队列
	std::map<int64_t, TimeRuner> m_TimerRuner_;
	const int kMicroSecondsPerSecond;
	// 下一个时间点
	void SetTimeFD(const int64_t& theTimeNext);
	// 多少时间后
	void InitTimerFD(const int64_t& theTimeNext);
};
#endif