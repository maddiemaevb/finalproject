#include "Server.h"
#include <iostream>
#include "Server.h"
#include <cstring>
#include <vector>
#include <mutex>
#include <thread>
#include <netinet/in.h>
#include <sys/socket.h>
#include <algorithm>
#include <unistd.h>

using namespace std;


Server::Server(int port) : running(false){
    serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (serverSocket == -1)
    {
        throw runtime_error("Error creating server socket.");
    }

	serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(port);
    serverAddress.sin_addr.s_addr = INADDR_ANY;
}


Server::~Server(){
    stopServer();
}


void Server::start() {
	std::cout << "Please type out any message and type exit to stop our chat!";

	while (true) {
		string message;
		cout << ": ";
		getline(cin, message);

		if (message == "exit") {
			std::cout << "Goodbye!" << endl;
			break;
		}

		sendMessage(message, -1);
	}
}

void Server::sendMessage(const string& message, int senderSocket) {
	for (int clientSocket : clientSocket) {
		if (clientSocket != senderSocket) {
			send(clientSocket, message.c_str(), message.length(), 0);
		}
	}
}

