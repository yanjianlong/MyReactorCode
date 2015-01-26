#ifndef __STDAFX_H
#define __STDAFX_H

#include <iostream>
#include <map>
#include <string>
#include <sys/socket.h>
#include <sys/epoll.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include <sys/time.h>
#include <fcntl.h>
#include <vector>
#include <pthread.h>
#include <unistd.h>
enum Event_Type
{
	ACCEPT_EVENT = 1,
	READ_EVENT = 2,
	WRITE_EVENT = 4,
	TIMEOUT_EVENT = 8,
	SIGNAL_EVENT = 16,
	CLOSE_EVENT = 32
};
const int MAX_EPOLL_EVENT = 10240;
using namespace std;
#endif