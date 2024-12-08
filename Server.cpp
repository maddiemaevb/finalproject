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


void Server::start(){
    if (bind(serverSocket, (struct sockaddr *)&serverAddress, sizeof(serverAddress)) == -1)
    {
        throw runtime_error("Error binding server socket.");
    }

    if (listen(serverSocket, 5) == -1)
    {
        throw runtime_error("Error listening on server socket.");
    }

    running = true;
    cout << "Server started. Waiting for clients..." << endl;

    while (running)
    {
        handleNewClient();
    }

}


void Server :: newClient(){
    sockaddr_in clientAddress;
    socklen_t clientAddrLen = sizeof(clientAddress);
    int clientSocket = accept(serverSocket, (struct sockaddr *)&clientAddress, &clientAddrLen);

    if (clientSocket != -1)
    {
        lock_guard<mutex> lock(clientMutex);
        clientSockets.push_back(clientSocket);
        cout << "Client connected!" << endl;

        thread([this, clientSocket]() {
            char buffer[1024];
            string username;
            bool firstMessage = true;

            while (true)
            {
                memset(buffer, 0, sizeof(buffer));
                int bytesRead = recv(clientSocket, buffer, sizeof(buffer), 0);
                if (bytesRead <= 0)
                {
                    lock_guard<mutex> lock(clientMutex);
                    clientSockets.erase(remove(clientSockets.begin(), clientSockets.end(), clientSocket), clientSockets.end());
                    cout << username << " disconnected." << endl;
                    close(clientSocket);
                    break;
                }

                if (firstMessage)
                {
                    username = buffer;
                    cout << username << " joined the chat." << endl;
                    sendMessageToAll(username + " joined the server.", clientSocket);
                    firstMessage = false;
                }
                else
                {
                    string message = username + ": " + buffer;
                    sendMessageToAll(message, clientSocket);
                }
            }
        }).detach();
    }

}

void Server::sendMessage(const string& message, int senderSocket) {
	for (int clientSocket : clientSocket) {
		if (clientSocket != senderSocket) {
			send(clientSocket, message.c_str(), message.length(), 0);
		}
	}
}

