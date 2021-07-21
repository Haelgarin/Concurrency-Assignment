#pragma once

namespace PLib
{
	enum SocketProtocol
	{
		DEFAULT, // Compilier/Service Provider decided
		ICMP,
		IGMP,
		RFCOMM,
		TCP = 6,
		UDP = 17,
		ICMPV6 = 58,
		RM = 113
	};
}