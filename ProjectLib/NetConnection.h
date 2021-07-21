#pragma once

#include <memory>
#include<unordered_map>
#include <string>
#include "INet4Address.h"
#include "INet6Address.h"
#include "PSocket.h"
#include "WinSockException.h"

namespace PLib
{
	class NetConnection
	{
	private:
	
		
	public:


		NetConnection();

		/*
		  Takes version numbers for the MAKEWORD macro.
		  If no version number is provided it defaults to 2.2
		*/ 
		void Startup(int highVerion = 2, int lowVersion = 2);
		

		void Cleanup();


		~NetConnection();
	};

}