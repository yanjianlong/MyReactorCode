#include "Channel.h"

Channel::Channel(const int& thesocket)
	: m_CallBackFun_(NULL)
	, m_socket_(thesocket)
	, m_waiteEvent_(0)
{}
Channel::~Channel()
{}

void Channel::setRecvEvent(const int& theEvent)
{
	m_recvEvent_ = theEvent;
}

void Channel::setCallBackFunction(IChannelCallBack* callBack)
{
	m_CallBackFun_ = callBack;
}

bool Channel::enableEvent(const int& epollfd, const int& theEvent)
{
	return update(epollfd, theEvent);
}

bool Channel::update(const int& epollfd, const int& theEvent)
{
	m_waiteEvent_ = m_waiteEvent_ | theEvent;
	if(m_socket_ == -1)
		return false;
	epoll_event ev;
	ev.data.ptr = this;
	ev.events = m_waiteEvent_;
	if(0 == epoll_ctl(epollfd, EPOLL_CTL_ADD, m_socket_, &ev))
		return true;
	return false;
}

bool Channel::handleEvent(const int& epollfd)
{
	switch(m_recvEvent_)
	{
	case EPOLLIN:		// 可读
		// std::cout << "EPOLLIN" << std::endl;
		{
			// 套接字字是否还有效
			if(m_CallBackFun_->ChannelCallBack(m_socket_))
			{
				return true;
			}
			else
			{
				// 套接字无效
				epoll_ctl(epollfd, EPOLL_CTL_DEL, m_socket_, NULL);
				return false;
			}
		}
		break;
	case EPOLLOUT:		// 可写
		std::cout << "EPOLLOUT" << std::endl;
		break;
	case EPOLLPRI:		// 紧急数据
		std::cout << "EPOLLPRI" << std::endl;
		break;
	case EPOLLRDHUP:	// 连接关闭，边缘触犯
		std::cout << "EPOLLRDHUP" << std::endl;
		break;
	case EPOLLERR:		// 错误
		std::cout << "EPOLLERR" << std::endl;
		break;
	case EPOLLET:		// 边缘触发
		std::cout << "EPOLLET" << std::endl;
		break;
	case EPOLLONESHOT:	// 之订阅一次事件，事件到来后需要重新订阅
		std::cout << "EPOLLONESHOT" << std::endl;
		break;
	case EPOLLHUP:
		std::cout << "EPOLLHUP" << std::endl;
		break;
	default:
		std::cout << "default:" << std::endl;
		break;
	}
	return true;
}

int Channel::get_Socket()
{
	return m_socket_;
}