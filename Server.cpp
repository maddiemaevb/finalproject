#include <iostream>
#include "Server.h"
#include <cstring>
#include <vector>
#include <mutex>
#include <thread>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>


using namespace std;


Server::Server(int port) {
	cout << "Hello, friend!";
}


void Server::start() {
	std::cout << "Please type out any message and type exit to stop our chat!";

	while (true) {
		std::string message;
		std::cout << ": ";
		std::getline(std::cin, message);

		if (message == "exit") {
			std::cout << "Goodbye!";
			break;
		}

		sendMessage(message);
	}
}

void Server::sendMessage(const string& message, int senderSocket) {
	for (int clientSocket : clientSockets) {
		if (clientSocket != senderSocket) {
			send(clientSocket, message.c(str(), message.length(), 0);
		}
	}
}
