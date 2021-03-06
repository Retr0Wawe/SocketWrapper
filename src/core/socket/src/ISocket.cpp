#include "ISocket.hpp"

#if defined(_WIN32) || defined(_WIN64)
#pragma comment(lib, "ws2_32.lib")
#include <winsock.h>
#endif

#include <cstdio>

namespace socketlib
{
	ISocket::ISocket(const char* _ip, uint16_t _port, eAddrType _addr_type) : is_init(TRUE)
	{
	#if defined(_WIN32) || defined(_WIN64)
		WSADATA ws_lib;

		if (WSAStartup(MAKEWORD(1, 1), &ws_lib) != 0) {
			std::printf("%s %d", "failed to winsock init", GetError());
			is_init = FALSE;
		}

		addr.sin_addr.S_un.S_addr = inet_addr(_ip);
	#else
		addr.sin_addr.s_addr = inet_addr(_ip);
	#endif
		addr.sin_family = AF_INET;
		addr.sin_port = htons(_port);
	}

	ISocket::ISocket() : sock(NULL), is_init(FALSE)
	{	}

	ISocket::ISocket(const ISocket& _serv)
	{
		this->addr = _serv.addr;
		this->sock = _serv.sock;
	}
	
	ISocket::~ISocket()
	{
		CloseSocket(sock);
	#if defined(_WIN32) || defined(_WIN64)
		WSACleanup();
	#endif
	}

	int ISocket::Shutdown(cock _sock, eShutdownType _how) const
	{
		return shutdown(_sock, int(_how));
	}

	const cock& ISocket::operator*() const
	{
		return sock;
	}

	void ISocket::operator=(const ISocket& _base)
	{
		if (this != &_base) {
			this->addr = _base.addr;
			this->sock = _base.sock;
		}
	}
}
