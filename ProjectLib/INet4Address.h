#pragma once

#include <iostream>
#include <string>
#include <WS2tcpip.h>
#include "Address.h"
#include "WinSockException.h"

namespace PLib
{
	class INet4Address : public Address
	{
	private:
		// Uses {} to initialise variables
		sockaddr_in address{};
		size_t length{};
	public:
		INet4Address();
		INet4Address(const char* add, int port);
		INet4Address(int port);

		sockaddr_in* GetSockaddrRef();

		size_t *GetSocketAddressLengthRef();
		size_t GetSocketAddressLengthVal();

		void GetSocketAddress(char*, int len);
		std::string GetSocketAddress();
		int GetPort();

		~INet4Address();
	};

}

