#include "PSocket.h"
#include "WinSockException.h"

namespace PLib
{
	// Default Constructor

	PSocket::PSocket() {}

	PSocket::PSocket(SOCKET sock)
	{
		sockfd = sock;
	}

	// Delegating Constructors

	PSocket::PSocket(std::shared_ptr<INet4Address> _addr) : PSocket{ _addr, SocketType::STREAM, SocketProtocol::DEFAULT }	{}

	PSocket::PSocket(std::shared_ptr<INet4Address> _addr, const SocketType &_type) : PSocket{ _addr, _type, SocketProtocol::DEFAULT} {}

	PSocket::PSocket(std::shared_ptr<INet4Address> _addr, const SocketProtocol &_protocol) : PSocket(_addr, SocketType::STREAM, _protocol) {}


	// Main Constructor

	PSocket::PSocket(std::shared_ptr<INet4Address> _addr, const SocketType &_type, const SocketProtocol &_protocol)
		: addr{ _addr }, type{ _type }, protocol{_protocol}
	{
		if ((sockfd = socket(addr->GetSockaddrRef()->sin_family, type, protocol)) == INVALID_SOCKET)
		{
			throw(WinSockException(WSAGetLastError()));
		}

		
	}

	void PSocket::Bind()
	{
		if (bind(sockfd, (sockaddr*)addr->GetSockaddrRef(), (int)addr->GetSocketAddressLengthVal()) == SOCKET_ERROR)
		{
			throw(WinSockException(WSAGetLastError()));
		}
	}

	void PSocket::Listen(int backlog)
	{
		if (listen(sockfd, backlog) != 0)
		{
			throw(WinSockException(WSAGetLastError()));
		}

		std::cout << addr->GetSocketAddress() << " - listening on port: " << addr->GetPort() << std::endl;
	}

	void PSocket::Accept(PSocket &clientSock)
	{
		
		clientSock.sockfd = accept(this->sockfd, (sockaddr*)this->addr->GetSockaddrRef(), (int*)this->addr->GetSocketAddressLengthRef());
		char buff[256];
		this->addr->GetSocketAddress(buff, sizeof(buff));
		std::cout << "Got connection from " << buff << ":" << this->addr->GetPort() << std::endl;
	}

	void PSocket::Connect()
	{
		if (connect(sockfd, (sockaddr*)addr->GetSockaddrRef(), (int)addr->GetSocketAddressLengthVal()) == SOCKET_ERROR)
		{
			std::cout << "Connect error" << std::endl;
			throw WinSockException(WSAGetLastError());
		}
	}

	int PSocket::Readn(char* data, int bytesToRead)
	{
		int nLeft = bytesToRead;
		int nRead;

		while (nLeft > 0)
		{
			if ((nRead = recv(sockfd, data, nLeft, 0) < 0))
			{
				if (errno == EINTR)
				{
					nRead = 0;
				}

				else
				{
					return -1;
				}
			}

			else
			{
				if (nRead == 0)
				{
					break;
				}

				else
				{
					nLeft -= nRead;
					data += nRead;
				}
			}
		}

		return bytesToRead - nLeft;
	}

	int PSocket::ReadSize()
	{
		int value = 0;
		char* recvBuffer = (char*)&value;
		Readn(recvBuffer, sizeof(int));

		return ntohl(value);
	}

	int PSocket::Writen(const char* data, int bytesToWrite)
	{
		int nLeft = bytesToWrite;
		int nWritten;

		while (nLeft > 0)
		{
			if ((nWritten = send(sockfd, data, nLeft, 0)) <= 0)
			{
				if (nWritten < 0 && errno == EINTR)
				{
					nWritten = 0;
				}

				else
				{
					return -1;
				}
			}

			else
			{
				nLeft -= nWritten;
				data += nWritten;
			}
		}

		return nLeft;
	}

	void PSocket::WriteSize(int size)
	{
		size = htonl(size);
		char* tosend = (char*)&size;
		Writen(tosend, sizeof(size));
	}

	int PSocket::GetPort()
	{
		return addr->GetPort();
	}

	SOCKET PSocket::GetSocketFD()
	{
		return sockfd;
	}

	void PSocket::SetSocketFD(SOCKET sock)
	{
		sockfd = sock;
	}

	bool PSocket::operator==(PSocket &rhs)
	{
		return sockfd == rhs.sockfd;
	}

	bool PSocket::operator!=(PSocket &rhs)
	{
		return sockfd != rhs.sockfd;
	}

	PSocket::~PSocket()
	{
		closesocket(sockfd);
	}



}