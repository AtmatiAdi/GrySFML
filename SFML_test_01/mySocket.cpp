#include "mySocket.h"

using namespace std;

SOCKET clientSocket, sock;
char buf[4096];

int mySocket::ClientInit() {
	int port = 54000;
	// Initalize winsock
	WSAData data;
	WORD ver = MAKEWORD(2, 2);
	int wsResult = WSAStartup(ver, &data);
	if (wsResult != 0) {
		// error
		return 1;
	}
	// Create socket
	sock = socket(AF_INET, SOCK_STREAM, 0);
	if (sock == INVALID_SOCKET) {
		// error
		return 2;
	}
	// Fill in a hint structure
	sockaddr_in hint;
	hint.sin_family = AF_INET;
	hint.sin_port = htons(port);
	inet_pton(AF_INET, ipAddres.c_str(), &hint.sin_addr);
	// Connect to srever
	cout << "Try to connect" << endl;
	int connResult = connect(sock, (sockaddr*)&hint, sizeof(hint));
	if (connResult == SOCKET_ERROR) {
		cout << "Can't connect to server, #" << WSAGetLastError() << endl;
		closesocket(sock);
		WSACleanup();
		return 3;
	}
	cout << "Connetced" << endl;
}

string mySocket::ClientSendAndEcho(string userInput) {
	// do to send and receive data
	if (userInput.size() > 0) {
		// Send the text
		int bytesRecived = 0;
		int sendResult = send(sock, userInput.c_str(), userInput.size() + 1, 0);
		if (sendResult != SOCKET_ERROR) {
			// wait for response
			ZeroMemory(buf, 4096);
			bytesRecived = recv(sock, buf, 4096, 0);
			if (bytesRecived == 0) {
				cout << "Recived empty message" << endl;
			}
		}
		return string(buf, 0, bytesRecived);
	}
	cout << "Dont try to send empty message" << endl;
	return string("");
}

void mySocket::ClientStop() {
	// Gracefully close down everything
	closesocket(sock);
	WSACleanup();
}

int mySocket::ServerInit() {
	// Init winsock
	WSADATA wsData;
	WORD ver = MAKEWORD(2, 2);
	int wsok = WSAStartup(ver, &wsData);
	if (wsok != 0) {
		// error
		return 1;
	}
	// Create socket
	SOCKET listening = socket(AF_INET, SOCK_STREAM, 0);
	if (listening == INVALID_SOCKET) {
		// error
		return 2;
	}
	// Bind the ip adress and port to a socket
	sockaddr_in hint;
	hint.sin_family = AF_INET;
	hint.sin_port = htons(54000);
	hint.sin_addr.S_un.S_addr = INADDR_ANY;
	bind(listening, (sockaddr*)&hint, sizeof(hint));
	// Tell winsock the socket is for listening
	listen(listening, SOMAXCONN);
	// Wait for connection
	sockaddr_in client;
	int clientSize = sizeof(client);
	clientSocket = accept(listening, (sockaddr*)&client, &clientSize);
	char host[NI_MAXHOST];
	char service[NI_MAXHOST];
	ZeroMemory(host, NI_MAXHOST);
	ZeroMemory(service, NI_MAXHOST);
	if (getnameinfo((sockaddr*)&client, sizeof(client), host, NI_MAXHOST, service, NI_MAXSERV, 0) == 0) {
		cout << host << "connected on port" << service << endl;
	}
	else {
		inet_ntop(AF_INET, &client.sin_addr, host, NI_MAXHOST);
		cout << host << "connected on port" << 
			ntohs(client.sin_port) << endl;
	}
	// Close listening socket
	closesocket(listening);
	

	return 0;
}

void mySocket::ServerStop() {
	// Close socket
	closesocket(clientSocket);
	// Shutdown winsock
	WSACleanup();
}

string mySocket::ServerRecivAndEcho(string echo) {
	// accept and echo message back to client
	ZeroMemory(buf, 4096);
	// wait for client to send data
	int bytesRecived = recv(clientSocket, buf, 4096, 0);
	if (bytesRecived == SOCKET_ERROR) {
		// error
		cout << "Error in recv" << endl;
		mySocket::ServerStop();
	}
	if (bytesRecived == 0) {
		cout << "Client disconnected" << endl;
	}
	// Echo message back to client
	send(clientSocket, echo.c_str(), echo.size() + 1, 0);
	return string(buf, 0, bytesRecived);
}