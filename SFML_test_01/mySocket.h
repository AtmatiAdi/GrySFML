#include <iostream>
#include <string>
#include <WS2tcpip.h>

#pragma comment (lib, "ws2_32.lib")

class mySocket
{
private:
	
public:
	std::string ipAddres = "127.0.0.1";
	int ClientInit();
	std::string ClientSendAndEcho(std::string userInput);
	void ClientStop();

	int ServerInit();
	std::string ServerRecivAndEcho(std::string echo);
	void ServerStop();
};

