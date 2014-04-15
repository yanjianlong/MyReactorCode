#include "Channel.h"

Channel::Channel(const int& thesocket)
	: m_CallBackFun_(NULL)
	, m_socket_(thesocket)
	, m_recvEvent_(0)
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

bool Channel::handleEvent(const int& epollfd)
{
	switch(m_recvEvent_)
	{
	case EPOLLIN:		// 可读
		// std::cout << "EPOLLIN" << std::endl;
		{
			// 套接字字是否还有效
			if(m_CallBackFun_->RecvDataCallBack(m_socket_))
				return true;
			else
				return false;
		}
		break;
	case EPOLLOUT:		// 可写
		std::cout << "EPOLLOUT" << std::endl;
		{}
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