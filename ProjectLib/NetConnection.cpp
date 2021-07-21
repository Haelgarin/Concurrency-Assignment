#include "NetConnection.h"

namespace PLib
{

	NetConnection::NetConnection() {}

	void NetConnection::Startup(int highVersion, int lowVersion)
	{
		WSADATA wsaData;
		if (int errorCode = WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
		{
			throw(WinSockException(errorCode)); // WSAStart returns the extended error code, so a call so WSAGetLastError() is not needed
		}
	}

	void NetConnection::Cleanup()
	{
		WSACleanup();
	}

	NetConnection::~NetConnection() {}
}