#pragma once

namespace PLib
{
	enum SocketType
	{
		STREAM = 1, // To ensure the numbering is the same as the winsock socket type - starts at zero otherwise
		DGRAM,
		RAW,
		RDM,
		SEQPACKET

	};
}