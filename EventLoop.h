#ifndef __EVENTLOOP_H__
#define __EVENTLOOP_H__
#include "Epoll.h"
#include "IAccepterCallBack.h"
#include "TimeQueue.h"
class EventLoop 
{
private:
	// 是否退出
	bool m_Quit_;
	// 删除连接者中的链接的回调函数
	IAccepterCallBack* m_deleteConnect_;
	/*
		时间回调的封装
	 */
	class RunClass
	{
	private:
		void* m_param_;
		IRunCallBack* m_runcallback_;
	public:		
		RunClass(IRunCallBack* theCallBack, void* theParam)
			: m_param_(m_param_)
			, m_runcallback_(theCallBack)
		{}
		~RunClass()
		{}
		void Run()
		{
			m_runcallback_->RunCallBack(m_param_);
		}
	};
	// 时间回调
	std::vector<RunClass> m_timefdCallBackClass_;
	TimeQueue* m_pTimeQueue_;
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
	void set_CallBack(IAccepterCallBack* theCallBack);

	// 关闭
	void CloseEventLoop();

	/*
		时间的回调
	 */
	void DoPendingFunctions();

	/// 返回定时器 fd
	// 定点调用
	int64_t runAt(const double& theTime, IRunCallBack* theCallBack);
	// 等待一段时间后调用
	int64_t runAfter(const double& theTime, IRunCallBack* theCallBack);
	// 每隔多少时间调用
	int64_t runEvery(const double& theTime, IRunCallBack* theCallBack);
	// 删除定时器
	void cancelTimer(const int64_t& timefd);
};

#endif