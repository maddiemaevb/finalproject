#include <iostream>
#include <sys/socket.h>
#include "Client.h"
#include <cstring>
#include <thread>
#include <arpa/inet.h>
#include <unistd.h>

using namespace std;

Client::Client(const string &serverIP, int serverPort, const string &username) : serverIP(serverIP), serverPort(serverPort), username(username) {}


void Client::connectToServer(){
    clientSocket = socket(AF_INET, SOCK_STREAM, 0);
    if(clientSocket == -1){
        throw runtime_error("Error with creating client socket.");
    }


    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(serverPort);
    inet_pton(AF_INET, serverIP.c_str(), &serverAddress.sin_addr);

    if (connect(clientSocket, (struct sockaddr *)&serverAddress, sizeof(serverAddress)) == -1){
        close(clientSocket);
        throw runtime_error("Error connecting to server.");
    }

    cout << "Connected to server as " << username << "." << endl;
}


void Client::start(){
    send(clientSocket, username.c_str(), username.length(), 0);

    thread receiveThread([this]() { getMess(); });

    string message;
    while (true){
        getline(cin, message);
        if (message == "/quit")
        {
            send(clientSocket, "User disconnected", 18, 0);
            close(clientSocket);
            cout << "Disconnected from server." << endl;
            exit(0);
        }

        string formattedMessage = username + ": " + message;
        send(clientSocket, formattedMessage.c_str(), formattedMessage.length(), 0);
    }

    receiveThread.join();
}

void Client::getMess(){
    char buffer[1024];
    while (true){
         memset(buffer, 0, sizeof(buffer));
        int bytesRead = recv(clientSocket, buffer, sizeof(buffer), 0);
        if (bytesRead <= 0) {
            cerr << "Disconnected from server." << endl;
            close(clientSocket);
            exit(0);
        }
        cout << buffer << endl;
    }
}
