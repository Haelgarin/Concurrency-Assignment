#pragma once
#include <memory>
#include <string>
#include <WinSock2.h>
#include "INet4Address.h"
#include "SocketType.h"
#include "SocketProtocol.h"

namespace PLib
{

	class PSocket
	{
	private:
		SOCKET sockfd;
		std::shared_ptr<INet4Address> addr;
		SocketType type; ;
		SocketProtocol protocol;  // protocol value of zero as default - protocol is decided automatically


	public:

		PSocket();
		PSocket(SOCKET sock);
		PSocket(std::shared_ptr<INet4Address> _addr);
		PSocket(std::shared_ptr<INet4Address> _addr, const SocketType &_type);
		PSocket(std::shared_ptr<INet4Address> _addr, const SocketProtocol &_protocol);
		PSocket(std::shared_ptr<INet4Address> _addr, const SocketType &_type, const SocketProtocol &_protocol);

		void Bind();
		void Listen(int backlog = 50);
		void Accept(PSocket &clientSock);
		
		void Connect();

		int Readn(char* data, int bytesToRead);
		int ReadSize();

		int Writen(const char* data, int bytesToWrite);
		void WriteSize(int size);

		int GetPort();
		SOCKET GetSocketFD();

		void SetSocketFD(SOCKET sock);

		bool operator==(PSocket &rhs);
		bool operator!=(PSocket &rhs);

		~PSocket();
	};

}
