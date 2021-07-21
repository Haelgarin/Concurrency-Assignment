#pragma once

namespace PLib
{
	class WinSockException : public std::exception
	{
	private:
		int code;
	public:
		WinSockException(int errorCode) noexcept : code{ errorCode } {}

		virtual char const* what() const noexcept
		{
			// Using error descriptions from https://docs.microsoft.com/en-us/windows/win32/winsock/windows-sockets-error-codes-2
			// Makes life easier compared to number error codes
			switch (code)
			{
			case 6:
				return "WSA_INVALID_HANDLE - Specified event object handle is invalid.";
				break;
			case 8:
				return "WSA_NOT_ENOUGH_MEMORY - Insufficient memory available.";
				break;
			case 87:
				return "WSA_INVALID_PARAMETER - One or more parameters are invalid.";
				break;
			case 995:
				return "WSA_OPERATION_ABORTED - Overlapped operation aborted.";
				break;
			case 996:
				return "WSA_IO_INCOMPLETE - Overlapped I/O event object";
				break;
			case 997:
				return "WSA_IO_PENDING - Overlapped operations will complete later.";
				break;
			case 10004:
				return "WSAEINTR - Interrupted function call";
				break;
			case 10009:
				return "WSAEBADF - File handle is not valid.";
				break;
			case 10013:
				return "WASEACCES - Permission denied";
				break;
			case 10014:
				return "WSAEFAULT - Bad address";
				break;
			case 10022:
				return "WSAEINVAL - Invalid argument";
				break;
			case 10024:
				return "WSAEMFILE - Too many open files.";
				break;
			case 10035:
				return "WSAEWOULDBLOCK - Rescource templorarily unavailable.";
				break;
			case 10036:
				return "WSAEINPROGRESS -  Operation now in progress.";
				break;
			case 10037:
				return "WSAEALREADY - Operation already in progress.";
				break;
			case 10038:
				return "WSAENOTSOCK - Socket operation on nonsocket.";
				break;
			case 10039:
				return "WSAEDESTADDRREQ - Destination address required.";
				break;
			case 10040:
				return "WASEMSGSIZE - Message too long.";
				break;
			case 10041:
				return "Protocol wrong type for socket.";
				break;
			case 10042:
				return "WSAENOPRTOOPT - Bad protocol option.";
				break;
			case 10043:
				return "WSAEPROTONOSUPPORT - Protocol not supported.";
				break;
			case 10044:
				return "WSAESOCKTNOSUPPORT - Socket type not supported.";
				break;
			case 10045:
				return "WSAEOPNOTSUPP - Operation not supported.";
				break;
			case 10046:
				return "WSAEPFNOSUPPORT - Protocol family not supported.";
				break;
			case 10047:
				return "WSAEAFNOSUPPORT - Address family not supported by protocol family";
				break;
			case 10048:
				return "WSAEADDRINUSE - Address already in use.";
				break;
			case 10049:
				return "WSAEADDRNOTAVAIL - Cannot assign requested address.";
				break;
			case 10050:
				return "WSAENETDOWN - Network is down.";
				break;
			case 10051:
				return "WSAENETUNREACH - Network in unreachable.";
				break;
			case 10052: 
				return "WSAENETRESET - Network dropped connect on reset.";
				break;
			case 10053:
				return "WSAECONNABORTED - Software caused connection abort.";
				break;
			case 10054:
				return "WSAECONNRESET - Connection reset by peer.";
				break;
			case 10055:
				return "WSAENOBUFS - No buffer space available.";
				break;
			case 10056:
				return "WSAEISCONN - Socket is already connected.";
				break;
			case 10057:
				return "WSAENOTCONN - Socket is not connected.";
				break;
			case 10058:
				return "WSAESHUTDOWN - Cannot send after socket shutdown.";
				break;
			case 10059:
				return "WSAETOOMANYREFS - Too many references.";
				break;
			case 10060:
				return "WSAETIMEDOUT - Conncetion timed out.";
				break;
			case 10061:
				return "WSAECONNREFUSED - Connection refused.";
				break;
			case 10062:
				return "WSAELOOP - Cannot translate a name.";
				break;
			case 10063:
				return "WSAENAMETOOLONG - Name too long.";
				break;
			case 10064:
				return "WSAEHOSTDOWN - Host is down.";
				break;
			case 10065:
				return "WSAEHOSTUNREACH - No route to host.";
				break;
			case 10066:
				return "WSAENOTEMPTY - Directory not empty.";
				break;
			case 10067:
				return "WSAEPROCLIM - Too many processes.";
				break;
			case 10068:
				return "WSAEUSERS - User quota exceeded.";
				break;
			case 10069:
				return "WSAEDQUOT - Disk quota exceeded.";
				break;
			case 10070:
				return "WSAESTALE - Stale file handle reference.";
				break;
			case 10071:
				return "WSAEREMOTE - Item is remote";
				break;
			case 10091:
				return "WSASYSNOTREADY - Network subsystem is unavailable.";
				break;
			case 10092:
				return "WSAVERNOTSUPPORTED - Winsock.dll version out of range.";
				break;
			case 10093:
				return "WSANOTINITIALISED - Successful WSAStartup not yet performed.";
				break;
			case 10101:
				return "WSAEDISCON - Graceful shutdown in progress.";
				break;
			case 10102:
				return "WSAENOMORE - No more results.";
				break;
			case 10103:
				return "WSAECANCELLED - Call has been canceled.";
				break;
			case 10104:
				return "WSAEINVALIDPROCTABLE - Procedure table is invalid.";
				break;
			case 10105:
				return "WSAEINVALIDPROVIDED - Service provider is invalid.";
				break;
			case 10106:
				return "WSAEPROVIDERFAILEDINIT - Service provider failed to initialise.";
				break;
			case 10107:
				return "WSASYSCALLFAILURE - System call failure.";
				break;
			case 10108:
				return "WSASERVICE_NOT_FOUND - Service not found.";
				break;
			case 10109:
				return "WSATYPE_NOT_FOUND - Class type not found.";
				break;
			case 10110:
				return "WSA_E_NO_MORE - No more results.";
				break;
			case 10111:
				return "WSA_E_CANCELLED - Call was canceled.";
				break;
			case 10112:
				return "WSAEREFUSED - Database query was refused.";
				break;
			case 11001:
				return "WSAHOT_NOT_FOUND - Host not found.";
				break;
			case 11002:
				return "WSATRY_AGAIN - Nonauthoritative host not found.";
				break;
			case 11003: 
				return "WSANO_RECOVERY - This is a nonrecoverable error.";
				break;
			case 11004:
				return "WSANO_DATA - Valid name, no data record of requested type.";
				break;
	
				// Remaining codes from 11005 to 11031 are QoS related error codes
				// I can't be bothered to lose my sanity any further than I already have by typing them out

			default:
				return "Error code: " + code;
			}
		}

		~WinSockException() = default;
	};
}
