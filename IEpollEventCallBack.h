#ifndef __IEPOLLEVENTCALLBACK_H__
#define __IEPOLLEVENTCALLBACK_H__

// 删除套接字
typedef bool (*EpollEventCallBack)(const int& thesocket);

#endif