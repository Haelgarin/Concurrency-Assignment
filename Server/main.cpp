#include <iostream>
#include <memory>
#include <thread>
#include <string>
#include <sstream>
#include <chrono>
#include <iomanip>

#include <ProjectLib/Shared.h>

using namespace PLib;

void ClientHandler(PSocket clientSock)
{

	while (true)
	{
		int incMessageSize = clientSock.ReadSize();
		char* incMessage = new char[incMessageSize + 1];
		clientSock.Readn(incMessage, incMessageSize);
		incMessage[incMessageSize] = '\0';

		std::stringstream ss;
		ss.str(incMessage);

		std::cout << incMessage << std::endl;

		delete[] incMessage;

		auto n = std::chrono::system_clock::now();
		auto in_time_t = std::chrono::system_clock::to_time_t(n);
		tm buf;
		localtime_s(&buf, &in_time_t);

		ss.clear();
		ss << std::put_time(&buf, "%Y-%m-%d %X");
		std::string time = ss.str();

		clientSock.WriteSize((int)time.length());
		clientSock.Writen(time.c_str(), (int)time.length());
		ss.clear();
		
		if (WSAGetLastError() == 10054)
		{
			std::cout << "Client Disconnected" << std::endl;
			break;
		}
	}

}

int main(int argc, char** argv)
{

	try
	{
		NetConnection netCntn;
		netCntn.Startup();

		auto listenAddress = std::make_shared<INet4Address>(50018);
		PSocket listenSock{ listenAddress };

		listenSock.Bind();
		listenSock.Listen();

		fd_set master;
		FD_ZERO(&master);
		FD_SET(listenSock.GetSocketFD(), &master);
		fd_set copy = master;
		

		while (true)
		{
			copy = master;

			// why do you return -1 after new fd gets added to master add it loops back round to you? 
			// What do you mean socket operation on nonsocket?
			int sockCount = select(0, &copy, NULL, NULL, NULL); 
		
			
			for (int i = 0; i < sockCount; i++)
			{
				PSocket sock(copy.fd_array[i]);
				if (sock.GetSocketFD() == listenSock.GetSocketFD())
				{
					PSocket clientSock;
					listenSock.Accept(clientSock);

					FD_SET(clientSock.GetSocketFD(), &master);
					std::string message = "Welcome to the chat server.\r\n";
					clientSock.WriteSize(message.length());
					clientSock.Writen(message.c_str(), message.length());
				}

				else
				{
					int messageSize = sock.ReadSize();
					char* incMessage = new char[messageSize + 1];
					if (sock.Readn(incMessage, messageSize) == -1)
					{
						closesocket(sock.GetSocketFD());
						FD_CLR(sock.GetSocketFD(), &master);
					}

					else
					{
						for (int i = 0; i < master.fd_count; i++)
						{
							PSocket outSock(master.fd_array[i]);
							if ((outSock != listenSock) && (outSock != sock))
							{
								outSock.WriteSize(messageSize);
								outSock.Writen(incMessage, messageSize);
							}

						}
					}
				}
			}



			
			
			
			
		}

		netCntn.Cleanup();

	}

	catch (WinSockException ex)
	{
		std::cout << ex.what() << std::endl;
		exit(-1);
	}



	return 0;
}