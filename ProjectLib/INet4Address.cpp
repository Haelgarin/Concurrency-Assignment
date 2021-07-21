#include "INet4Address.h"

namespace PLib
{
	INet4Address::INet4Address() {}

	INet4Address::INet4Address(const char* add, int port)
	{

		memset(&address, 0, sizeof(address)); // zero out memeory
		address.sin_family = AF_INET;
		address.sin_port = htons(port);

		int result = inet_pton(AF_INET, add, &address.sin_addr);
		length = sizeof(address);

		if (result == 1)
		{
			return;
		}

		addrinfo hints{};
		hints.ai_family = AF_INET;
		addrinfo* hostInfo = nullptr;

		result = getaddrinfo(add, NULL, &hints, &hostInfo);

		if (result == 0)
		{
			sockaddr_in* hostAddr = (sockaddr_in*)(hostInfo->ai_addr);

			address.sin_addr = hostAddr->sin_addr;
		}

		else
		{
			throw WinSockException(result);
		}


		
	}

	INet4Address::INet4Address(int port)
	{
		memset(&address, 0, sizeof(address));
		address.sin_family = AF_INET;
		address.sin_port = htons(port);
		address.sin_addr.s_addr = htonl(INADDR_ANY);
		length = sizeof(address);
	}

	sockaddr_in* INet4Address::GetSockaddrRef()
	{
		return &address;
	}

	size_t* INet4Address::GetSocketAddressLengthRef()
	{
		return &length;
	}

	size_t INet4Address::GetSocketAddressLengthVal()
	{
		return length;
	}

	void INet4Address::GetSocketAddress(char* cstr, int len)
	{
		inet_ntop(AF_INET, &address.sin_addr, cstr, len);
	}

	std::string INet4Address::GetSocketAddress()
	{
		char tString[INET_ADDRSTRLEN];

		GetSocketAddress(tString, INET_ADDRSTRLEN);
		return std::string(tString);
	}

	int INet4Address::GetPort()
	{
		return ntohs(address.sin_port);
	}



	INet4Address::~INet4Address() {}

}

