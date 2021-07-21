#include <iostream>
#include <string>
#include <sstream>
#include <ProjectLib/Shared.h>

using namespace PLib;

int main(int argc, char** argv)
{
	try
	{
		NetConnection netCntn;

		netCntn.Startup();

		auto serverAddress = std::make_shared<INet4Address>("Amys-Computer", 50018);

		PSocket clientSock{ serverAddress };

		clientSock.Connect();
		
		//fd_set master;
		//FD_ZERO(&master);
		//FD_SET(clientSock.GetSocketFD(), &master);

		while (true)
		{
			/*fd_set copy = master;
			int sockCount = select(0, &copy, nullptr, nullptr, nullptr);*/


	
			int incMessageSize = clientSock.ReadSize();
			char* incMessage = new char[incMessageSize + 1];
			clientSock.Readn(incMessage, incMessageSize);
			incMessage[incMessageSize] = '\0';

			std::cout << incMessage << std::endl;
				

			delete[] incMessage;
			

		
			std::cout << ">> ";

			std::string outMessage;
			std::getline(std::cin, outMessage);

			clientSock.WriteSize(outMessage.length());
			clientSock.Writen(outMessage.c_str(), outMessage.length());
			
			
			

			
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