#ifndef CLIENT_TCP_HPP_
#define CLIENT_TCP_HPP_

#include "ISocket.hpp"

namespace socketlib
{
	class ClientTcp : public ISocket
	{
	public:
		ClientTcp(const char* _ip, std::uint16_t _port, eAddrType _addr_type = eAddrType::IPv4);
		
		explicit ClientTcp(const ClientTcp& _client);

		~ClientTcp() = default;
	public:
		int Connect() const;

		virtual len_t Send(cock _sock, const char* _buf, int _flags = 0) const;

		virtual len_t Receive(cock _sock, char* _buf, len_t _buf_len, int _flags = 0) const;
	public:
		ClientTcp& operator=(const ClientTcp& _client);
	};
}

#endif // !CLIENT_TCP_HPP_
